
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv)
{
    // seems to only happen on wayland

#ifndef __APPLE__
    SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "wayland");
#endif // !__APPLE__

    // init
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        return SDL_APP_FAILURE;
    }

    // create a window
    window = SDL_CreateWindow(
        "SDL Minimal Bug Sample", 400, 200,
        SDL_WINDOW_RESIZABLE);

    if (!window) {
        return SDL_APP_FAILURE;
    }

    // create a renderer just to make window show up
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        return SDL_APP_FAILURE;
    }

    // i have experienced this "zero window id" bug with some other ways and platforms (linux and macos to be specific
    // not tested on windows) but i have no way of consistently executing them.
    //
    // the only way i know that im consistently able to execute is by using SDL_SetWindowRelativeMouseMode.
    SDL_SetWindowRelativeMouseMode(window, true);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{

    SDL_SetWindowRelativeMouseMode(window, true);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{

    switch (event->type) {

    case SDL_EVENT_WINDOW_RESIZED: {
        if (event->window.windowID == 0)
            SDL_Log("(SDL_EVENT_WINDOW_RESIZED) event window id '0' emitted");

        break;
    }

    case SDL_EVENT_WINDOW_CLOSE_REQUESTED: {
        if (event->window.windowID == 0)
            SDL_Log("(SDL_EVENT_WINDOW_CLOSE_REQUESTED) event window id '0' emitted");

        break;
    }

    case SDL_EVENT_KEY_DOWN: {
        if (event->key.windowID == 0)
            SDL_Log("(SDL_EVENT_KEY_DOWN) event window id '0' emitted");
        break;
    }

    case SDL_EVENT_KEY_UP: {
        if (event->key.windowID == 0)
            SDL_Log("(SDL_EVENT_KEY_UP) event window id '0' emitted");
        break;
    }

    case SDL_EVENT_TEXT_INPUT: {
        if (event->text.windowID == 0)
            SDL_Log("(SDL_EVENT_TEXT_INPUT) event window id '0' emitted");
        break;
    }

    case SDL_EVENT_MOUSE_BUTTON_DOWN: {
        if (event->button.windowID == 0)
            SDL_Log("(SDL_EVENT_MOUSE_BUTTON_DOWN) event window id '0' emitted");
        break;
    }

    case SDL_EVENT_MOUSE_BUTTON_UP: {
        if (event->button.windowID == 0)
            SDL_Log("(SDL_EVENT_MOUSE_BUTTON_UP) event window id '0' emitted");
        break;
    }

    case SDL_EVENT_MOUSE_MOTION: {

        if (event->motion.windowID == 0)
            SDL_Log("(SDL_EVENT_MOUSE_MOTION) event window id '0' emitted");

        break;
    }

    case SDL_EVENT_MOUSE_WHEEL: {
        if (event->wheel.windowID == 0)
            SDL_Log("(SDL_EVENT_MOUSE_WHEEL) event window id '0' emitted");
        break;
    }

    case SDL_EVENT_QUIT: {

        return SDL_APP_SUCCESS;
    }
    }

    // if (event->type == SDL_EVENT_QUIT) {
    //     return SDL_AppResult::SDL_APP_SUCCESS;
    // }
    //
    if (event->type == SDL_EVENT_MOUSE_MOTION) {
        SDL_Log("MouseMotion window id %i", event->motion.windowID);
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    if (window)
        SDL_DestroyWindow(window);
}
