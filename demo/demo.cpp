#include <viewer.h>
#include <cstddef>

#include <iostream>

int main(int argc, char** argv)
{
    /* library functionality is exposed through the Viewer class */
    Viewer viewer;

    /* define initial viewer settings */
    viewer.mWindow.title = "Viewer Demo";
    viewer.mWindow.width = 1280;
    viewer.mWindow.height = 720;
    viewer.mWindow.vsync = true;
    viewer.mWindow.mHDPI = true;


    /* called before main loop executes (should be used to initialize gl resources) */
    viewer.onInit([&]()
    {
        viewer.mCamera.size /= 100.0f;
        viewer.mRender.pointRadius = 5.0f;
        viewer.mRender.lineWidth = 2.0f;
        viewer.mRender.circleVertices = 32;
        viewer.mRender.wireframe = false;
    });


    /* called once per frame */
    viewer.onUpdate([&](Window& window, double dt)
    {
        /* access keyboard and mouse */
        auto& kb = window.keyboard();
        auto& mp = window.mouse();

        /* example: access keyboard state and move camera accordingly */
        glm::dvec2 move(0, 0);
        move.x -= kb[GLFW_KEY_A] ? 1.0 : 0.0;
        move.x += kb[GLFW_KEY_D] ? 1.0 : 0.0;
        move.y += kb[GLFW_KEY_W] ? 1.0 : 0.0;
        move.y -= kb[GLFW_KEY_S] ? 1.0 : 0.0;
        viewer.mCamera.position += dt * move;
    });


    /* called once per frame and should be used to draw primitives */
    viewer.onDraw([&](Window& window, double dt)
    {
        /* draw points */
        std::vector<glm::vec2> points = { {1.5, 2.0}, {3.0, 2.0}, {1.5, 1.0}, {3.0, 1.0} };
        viewer.drawPoints(points.begin(), points.end(), [](auto& p, auto& coord, auto& color)
        {
            coord = p;
            color = {0.0, 0.0, 1.0, 1.0};
            return true;
        });

        /* draw lines */
        std::vector< std::pair<glm::vec2, glm::vec2> > lines = { {{1.5, 2.0}, {3.0, 2.0}}, {{1.5, 1.0}, {3.0, 2.0}}, {{1.5, 1.0}, {3.0, 1.0}} };
        viewer.drawLines(lines.begin(), lines.end(), [](auto& l, auto& start, auto& end, auto& color)
        {
            start = l.first;
            end = l.second;
            color = {1.0, 0.0, 0.0, 1.0};
            return true;
        });

        /* draw circles */
        std::vector< std::pair<glm::vec2, float> > circles = { {{2.5, -1.0}, 0.25}, {{2.5, 0.0}, 0.5} };
        viewer.drawCircles(circles.begin(), circles.end(), [](auto& c, auto& pos, auto& radius, auto& color)
        {
            pos = c.first;
            radius = c.second;
            color = {0.0, 1.0, 0.0, 1.0};
            return true;
        });

        /* draw quad */
        viewer.drawQuad({-2.0, -2.0}, {-1.0, -2.0}, {-1.0, -1.0}, {-2.0, -1.0}, {0.0, 1.0, 0.0, 1.0});

        /* draw triangle mesh */

        /* draw textured rectangle */

        /* render ground */
        viewer.drawBoundary(glm::vec2{0, -1.5f}, {0, 1}, 10.0f, 0.5f);
    });


    /* called once per frame to draw user interface with imgui/implot */
    viewer.onGui([&](Window& window, double dt)
    {
        ImGui::ShowDemoWindow();
        ImPlot::ShowDemoWindow();
    });


    /* callback for key events */
    viewer.onKey([&] (Window& window, Keyboard& keyboard, int key, int mod, bool press)
    {
        if(!press) return;

        /* close application */
        if(key == GLFW_KEY_ESCAPE) { window.close(true); }

        /* fullscreen toggle */
        if(key == GLFW_KEY_F) { window.fullscreen( !window.fullscreen() ); }

        /* zoom in */
        if(key == GLFW_KEY_Q) { viewer.mCamera.zoom -= 0.25f; }

        /* zoom out */
        if(key == GLFW_KEY_E) { viewer.mCamera.zoom += 0.25f; }
    });


    /* callback for mouse button events */
    viewer.onMouseButton([&](Window& window, Mouse& mouse, int button, int mod, bool press)
    {
        /* access relative mouse coordinates */
        auto pos = mouse.position();

        /* convert to world space position */
        auto world_pos = viewer.worldSpacePosition(pos);
    });

    /* start viewer: create gl context - call init callback and run mainloop until window is closed */
    viewer.run();

    return EXIT_SUCCESS;
}
