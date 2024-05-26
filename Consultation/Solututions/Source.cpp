#include "EventManager.h"

int main()
{
    EventManager e;

    e.addEventListener("ffile.txt");
    e.addEventListener("t5");

    e.addEventResponse("stdout");
    e.addEventResponse("foutfile.txt");

    // При промяна на file.txt и на всеки 30 секунди
    // във файла outfile.txt и на стандартния изход ще се 
    // изписват съответните съобщения.
    e.run();

}
