set -e

# Variables
root_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cmake_build_dir="${root_dir}/build"
cpplint="${root_dir}/3rdparty/cpplint.py"
github_api_repo="https://api.github.com/repos/UNN-VMK-Software/devtools-course-practice"

# This function executes command and stops execution if return status isn't 0
function try {
    "$@"
    status=$?
    if [ $status -ne 0 ]; then
        echo "ERROR with '$@' in $dir"
        exit $status
    fi
    return $status
}

function Header {
    echo ""
    echo "*****************************************************"
    echo "$@"
    echo "*****************************************************"
    echo ""
}

function Clean {
    rm -rf $cmake_build_dir
}

function CheckGoogleStyleInDir {
    retCode=0

    # hpp_files=`find . -name "*.hpp"`
    # if [[ $hpp_files ]]; then
    #     echo "ERROR: Please use *.h extension instead of *.hpp:"
    #     echo " - $hpp_files"
    #     retCode=1
    # fi

    echo "Checking $module"
    sources=`find . -name "*.hpp" -or -name "*.h" -or -name "*.cpp" -or -name "*.cxx"`
    for file in $sources;
    do
        python $cpplint $file
        status=$?
        if [ $status -ne 0 ]; then
            retCode=$status
        fi
    done

    return $retCode
}

# Go through all directories and check Google style
function CheckGoogleStyle {
    Header "Check \"Google C++ Style\""

        cd src
        try CheckGoogleStyleInDir
        cd $root_dir
        echo ""

        cd include
        try CheckGoogleStyleInDir
        cd $root_dir
        echo ""

        cd samples
        try CheckGoogleStyleInDir
        cd $root_dir
        echo ""
}

function BuildCMakeProject {
    Header "Build common CMake project"

    dir=$cmake_build_dir
    mkdir -p $cmake_build_dir
    cd $cmake_build_dir
    try cmake -DCOVERAGE=ON -DCMAKE_BUILD_TYPE=Debug $root_dir
    try make
}

function CTest {
    Header "Run all CTest tests"
    try ctest --output-on-failure
}

function GoogleTest {
    Header "Run all GoogleTest tests"

    for test in $(ls -1 ./bin/test_*)
    do
        Header "Testing $test"
        try $test
    done
}

function Main {
    # Clean
    CheckGoogleStyle
    BuildCMakeProject
    CTest
    GoogleTest
}

Main

