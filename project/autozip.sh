#!/bin/bash
echo "Running '$@' on file change in lib/"
echo "Autoruns on file update"

zip -r ScreenRender lib/ScreenRender/*

while true; do
    # Wait for any file changes recursively in the current directory.
    file=$(inotifywait -r -e modify,create,delete,move -q --format "%e %w %f" ./lib)

    # Extract the event, directory, and filename.
    event=$(echo "$file" | awk '{print $1}')
    dir=$(echo "$file" | awk '{print $2}')
    filename=$(echo "$file" | awk '{print $3}')

    # Check if the changed file has a .cpp or .hpp extension.
    if [[ "$filename" =~ \.cpp$ || "$filename" =~ \.h$ ]]; then
        echo -e "\n\n\n\n"
        echo "Detected change in $filename"

        # Run the command
        # shellcheck disable=SC2068
        
        zip -r ScreenRender lib/ScreenRender/*
    fi
done
