#include <string>

#define DllExport   __declspec( dllexport )

using namespace std;

class DllExport Exporter {
public:
    Exporter();

    void SetUpImgui(struct GLFWwindow* window);

};