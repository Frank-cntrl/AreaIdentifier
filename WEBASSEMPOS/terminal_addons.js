// terminal_addons.js
// This library provides JavaScript functions that can be called from C++ via Emscripten.

var LibraryTerminalAddons = {
    // This function will clear the terminal output in the HTML page.
    // It is called from C++ (e.g., via `EM_ASM(clearTerminalOutput());` or `ccall`)
    // This assumes you have an HTML element with id 'output' or similar where terminal content is displayed.
    // The implementation details depend on your specific HTML structure.
    clearTerminalOutput: function() {
        // Example: If you have a <pre> or <div> with id="output" for terminal display
        // var outputElement = document.getElementById('output');
        // if (outputElement) {
        //     outputElement.innerHTML = ''; // Clear its content
        // }
        // Or, if using a library like xterm.js, you'd call its clear method.
        // For now, it's a placeholder. The C++ `clearScreen` function will likely be empty
        // or trigger a prompt to clear the visible console in the browser if one exists.
        console.log("Terminal clear requested from C++.");
        // In a real browser-based terminal, you'd integrate with its API to clear.
        // For simplicity, we'll just log it.
    },

    // Add other JavaScript functions here that your C++ code might need to interact with the browser.
    // For example, functions to manipulate the DOM, play sounds, etc.
};

// Register the library with Emscripten
autoAddDeps(LibraryTerminalAddons, '$clearTerminalOutput');