#include <stdio.h>
#include "renderer_ascii.h"
#include "math.h"

int sleep(long miliseconds);

int main(int argc, char* argv[]){
    RdScreen window = rdCreateScreen(21, 13);

    RdVertex2f v0 = {-0.5f, -0.5f, 48.0f};
    RdVertex2f v1 = {-0.4f, 0.5f, 58.0f};

    rdClear(&window);
    rdLine2f(&v0, &v1, &window);
    rdRender(&window);

    rdDestroyScreen(&window);
    return 0;
}

int sleep(long miliseconds){
   struct timespec req, rem;

   if(miliseconds > 999)
   {   
        req.tv_sec = (int)(miliseconds / 1000);                            /* Must be Non-Negative */
        req.tv_nsec = (miliseconds - ((long)req.tv_sec * 1000)) * 1000000; /* Must be in range of 0 to 999999999 */
   }   
   else
   {   
        req.tv_sec = 0;                         /* Must be Non-Negative */
        req.tv_nsec = miliseconds * 1000000;    /* Must be in range of 0 to 999999999 */
   }   

   return nanosleep(&req , &rem);
}