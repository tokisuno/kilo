# Kilo
Kilo is a lightweight CLI text editor. It's also not an original creation. I am just following this guide/tutorial on how to write a CLI text editor from scratch in C.

[Here's the link to the tutorial!](https://viewsourcecode.org/snap token/kilo/)

# Lessons learned
## We take these tools for granted
I mean, we all use text editors without thinking about how exactly they work. Even with this very primitive version of a text editor, it's still very eye-opening to how intricate they can be. This is the barebones code you get from completing the tutorial, and after all of that you still don't have a function undo/redo, you don't have tabs/buffers, and the search is essentially O(1). It's just iterating through a stringified version of the text buffer and doing ``strncmp()``.

## strstr()
I had no idea that this was a function that existed, but it actually blew my mind when I saw it. I know it isn't that big of a deal, but I'm still someone who functions under the opinion that C makes you write everything and work for it. I was really glad to experiment/use all of these different libraries.

## Disabling default terminal behaviours
When covering ``termios``, my mind was once again blown. The minute I learned about ``<termios.h>`` and what it does, I went over the Neovim source code to see if it was used there. Sure enough, it is! Seeing how these applications have to mute a lot of pre-existing flags and key-codes was interesting. I didn't even think about dealing with (by disabling) input-processing in the first place.

## Handling user input
Honestly I just didn't realize how important input handling was as a program concept in general, and this project really drilled that in. Combining what was learned with using ``termios``, it's also required to display/handle a bunch of other keys that shouldn't print any output. By default, we were printing all the scan codes to the terminal. Then, we had to implement proper visualization of TAB and ESC and BKSP. It completely slipped my mind that we'd have to actually write what backspace does.

Since I've done casual game-development projects, handling basic user input navigation made sense to me. Everything globally is handled with the ``editorConfig`` struct, which contains basically everything involving the user's global state, along with the editor itself.

## Syntax highlighting is wild
I've been using Treesitter for so long that I forgot how much of a blessing just having default native syntax highlighting can be. It really makes me appreciate the work that's been put into Neovim. Neovim introduced asynchronous Treesitter in version 0.11, which has GREATLY helped with performance and the overall user experience. I cannot even FATHOM or IMAGINE implementing such a thing into Kilo. That's way out of my scope.
