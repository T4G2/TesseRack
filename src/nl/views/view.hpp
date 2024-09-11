#pragma once
#include "../driver.hpp"

namespace nl {

    class App;

    class View {
    public:
        View() = default;
        virtual void render(App& app) = 0;
    };

}