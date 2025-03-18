#include <iostream>
#include <fstream>
#include <graphics.h>
#include <cstring>
#include <string>
#include <cctype>

#include "adder.h"
#include "adder_frontend.h"

using namespace std;

//int de_unde_se_citeste = 1;     //daca e 1 = presets, 2 = input_text



int main()
{
    initialize_buttons();           ///pune informatia in butoanele principale
    program.initialize_program();   ///
    start.draw_menu();

    int yDiagram = 50;
    int wDiagram = 1000;

    while(!ok)
    {
        mx = mousex();
        my = mousey();
        if(curent == 0)
        {
            start.hoover(mx, my);
            info.hoover(mx, my);
            settings.hoover(mx, my);
            chat.hoover(mx, my);
            exitt.hoover(mx, my);
        }
        else if(curent == 1)
        {
            diagram.hoover(mx, my);
            presets.hoover(mx, my);
            bck.hoover(mx, my);
        }
        else if(curent == 2)
        {
            atribuire.hoover(mx, my);
            daca.hoover(mx, my);
            pentru.hoover(mx, my);
            cat_timp.hoover(mx, my);
            pana_cand.hoover(mx, my);
            cazuri.hoover(mx, my);
            back_info.hoover(mx, my);
        }

        else if(curent == 3)
        {
            language.hoover(mx, my);
            back_settings.hoover(mx, my);
        }
        else if(curent == 4)
        {
            bck.hoover(mx , my);
            zoom_in.hoover(mx, my);
            zoom_out.hoover(mx, my);
            scroll_left.hoover(mx, my);
            scroll_right.hoover(mx, my);
            scroll_up.hoover(mx, my);
            scroll_down.hoover(mx, my);
            download.hoover(mx, my);
            for(int i=0; i<indexAtr; i++)
                atr[i].hoover(mx, my);
            for(int i=0; i<indexDaca; i++)
                dac[i].hoover(mx, my);
            for(int i=0; i<indexCtt; i++)
                ctt[i].hoover(mx, my);
            for(int i=0; i<indexPtr; i++)
                ptr[i].hoover(mx, my);
            for(int i=0; i<indexRep; i++)
                rep[i].hoover(mx, my);
            for(int i=0; i<indexCaz; i++)
                caz[i].hoover(mx, my);
        }
        else if(curent == 5)
        {
            back_info.hoover(mx, my);
        }
        else if(curent == 6)
        {
            bck2.hoover(mx, my);
        }

        if(ismouseclick(WM_LBUTTONDOWN))
        {
            start.search_for_mouse_activity();
            //clearmouseclick(WM_LBUTTONDOWN);
        }
    }
    closegraph();

    return 0;
}
