
#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

GLFWwindow* controller_hWnd;

void control_applet() {

    glfwWindowHint( GLFW_MOUSE_PASSTHROUGH, GLFW_FALSE );
    glfwWindowHint( GLFW_DECORATED, GLFW_TRUE );
    glfwWindowHint( GLFW_FOCUS_ON_SHOW, GLFW_TRUE );
    glfwWindowHint( GLFW_VISIBLE, GLFW_FALSE);

    controller_hWnd = glfwCreateWindow(1280, 960, "soooubway game", nullptr, nullptr);

    glfwMakeContextCurrent(controller_hWnd);
    glfwSwapInterval( 0 );


    glfwShowWindow(controller_hWnd);

    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(controller_hWnd, true);
    ImGui_ImplOpenGL3_Init();

 //   ImGui::GetIO().Fonts->AddFontFromFileTTF("lowiro!.ttf", 16.0f);

    ImGui::GetIO().Fonts->AddFontDefault();

    
  //  glfwHideWindow(controller_hWnd);

}

void BrowserController_render();
void BrowserController2_render();

void run_control_applet() {

    if (!glfwGetWindowAttrib(controller_hWnd, GLFW_VISIBLE))
        return;

    if (glfwWindowShouldClose(controller_hWnd)) {
        glfwHideWindow(controller_hWnd);
    }
    
    glfwMakeContextCurrent(controller_hWnd);

    glClearColor(0.98f, 0.98f, 0.98f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();



    ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(0,0,0, 64));
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("xx", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus );

  //  BrowserController_render(); // parousia main
    BrowserController_render(); // metro

    ImGui::End();
    ImGui::PopStyleColor();



    ImGui::EndFrame();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(controller_hWnd);
    glfwPollEvents();
    
}

extern "C" void show_control_applet() {
    glfwSetWindowShouldClose(controller_hWnd, GL_FALSE);
    glfwShowWindow(controller_hWnd);
}

int main() {

    glfwInit();

	glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_API );


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
 //   glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);


    control_applet();

    for (; !glfwWindowShouldClose(controller_hWnd); ) {
        run_control_applet();
    }
//   test.destroy();

    glfwTerminate();
}