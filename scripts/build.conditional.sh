if ./build.sh && [[ $? -eq 0 ]] ; then
    echo ""
    echo "Build succeeded!"
    echo ""
else
    echo ""
    echo "Build failed. Press any key to exit..."
    read -n 1 -s
fi