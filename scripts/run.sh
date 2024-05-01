if ./build.sh && [[ $? -eq 0 ]] ; then
    echo ""
    echo "Running the program..."
    echo ""
    ./bin/Debug/vulk.exe
else
    echo ""
    echo "Build failed. Press any key to exit..."
    read -n 1 -s
fi