int curent=0;
bool ok = false;
int limba=1; //0 = engleza, 1 = romana

char incepe[100][30] = {"Start", "Incepe"};
char informatii[100][30] = {"Info", "Info"};
char setari[100][30] = {"Settings", "Setari"};
char inapoi[100][30] = {"Back", "Inapoi"};
char llimba[100][30] = {"Language", "Limba"};

char diagrama[100][30] = {"Diagram", "Diagrama"};
char salvare[100][30] = {"Presets", "Salvare"};

char aatribuire[100][30] = {"Assign", "Atribuire"};
char ddaca[100][30] = {"If", "Daca"};
char ppentru[100][30] = {"For", "Pentru"};
char ccattimp[100][30] = {"While", "Cat timp"};
char ppanacand[100][30] = {"Repeat until", "Repeta"};
char ccazuri[100][30] = {"Switch", "Cazuri"};


char sintax_atr[100][30] = {"Assign-Syntax", "Sintaxa-Atribuire"};
char sintax_daca[100][30] = {"If-Syntax", "Sintaxa-Daca"};
char sintax_pentru[100][30] = {"For - Syntax", "Sintaxa - Pentru"};
char sintax_cattimp[100][30] = {"While - Syntax", "Sintaxa - Cat timp"};
char sintax_panacand[100][30] = {"Repeat until - Syntax", "Sintaxa - Repeta pana cand"};
char sintax_cazuri[100][30] = {"Switch - Syntax", "Sintaxa - Cazuri"};

char saves[100][30] = {"Download", "Descarca"};


void re_initialize_buttons();
void updateFilePortion(const string& filename, const string& newContent, const string& marker);


class initializer{                             //diagram
public:
    void initialize_program()
    {
        read_input();
        Initializare_nod(a, "{}", 0, -1);
        arbore(n, a);
    }
};

class screen{
public:
    const char* img;                            //the image that opens
    int sheight = getmaxheight();               //height of the screen
    int swidth = getmaxwidth();                 //width of the screen
    void open_image()                           //opens the background image
    {
        initwindow(swidth, sheight, "Nassi-Schneidermann", 0, 0);
        readimagefile(img, 0, 0, swidth, sheight);
    }
    void close_screen()
    {
        getch();
        closegraph();
    }
};

class start_screen : public screen{
public:
    start_screen(){
        img = "start_image.img";
    }
};

class button{
public:
    int current_pos = 0;
    int redraw = 0;
    int top, bottom, left, right;                    //coordonates
    int width, height;                               //dimensions
    int button_color, frame_color, text_color;       //color of the button and of the frame surrounding the button
    char text[30];                                   //text inside the button
    int text_length, text_height;                    //length and height of text
    void create_button()
    {
        setfillstyle(1, button_color);
        bar(top, left, bottom, right);
        setcolor(frame_color);
        setlinestyle(0, 0, 2);
        rectangle(top, left, bottom, right);
    }
    void put_text()
    {
        int x, y;                                   //coordinates of the text where it starts
        setcolor(text_color);                       //we set the text color
        setbkcolor(button_color);                   //we set the background text color
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);   //we set the font, dimension, direction
        text_height = textheight(text);             //we save the height and length only after aplying fonts
        text_length = textwidth(text);
        x = top + width/2 - text_length/2;          //x starts from the x of the button, we add half the width of the button and substract the half the length of the text
        y = left + height/2 - text_height/2;        //y starts from the y of the button, we add half of the height of the button and substract half od the height of the text
        outtextxy(x, y, text);
    }
   void open_window(int a, int b)
    {
        initgraph(&a, &b, "");
    }
    bool is_inside_button()
    {
        clearmouseclick(WM_LBUTTONDOWN);
        mx = mousex();
        my = mousey();
        return (mx >= top && mx <= top + width && my >= left && my <= left + height);
    }
    bool is_inside_button(int x, int y)
    {
        return (x >= top && x <= top + width && y >= left && y <= left + height);
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = DARKGRAY;
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = LIGHTGRAY;
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            put_text();
            redraw = 0;
        }
    }
    void search_for_mouse_activity();
    void draw_menu();
};


class assign_button : public button {
public:
    int contor_command=0;                              //comanda butoanelor de pe diagrama
    assign_button()
    {
        button_color = COLOR(230,230,250);
        frame_color = 1;
        width = 1000 +s_in_out;
        height = 50+s_in_out;
    }
    void put_text()
    {
        int x, y;                                   //coordinates of the text where it starts
        setcolor(text_color);                       //we set the text color
        setbkcolor(button_color);                   //we set the background text color
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);   //we set the font, dimension, direction
        text_height = textheight(text);             //we save the height and length only after aplying fonts
        text_length = textwidth(text);
        x = top + width/2 - text_length/2;          //x starts from the x of the button, we add half the width of the button and substract the half the length of the text
        y = left + height/2 - text_height/2;        //y starts from the y of the button, we add half of the height of the button and substract half od the height of the text
        outtextxy(x, y, text);
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(199,199,243);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(230,230,250);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            put_text();
            redraw = 0;
        }
    }
    void edit_button()
    {
        string unchanged_text(text);

        char sirnou[MAX];
        char Enter = 13, BackSpace = 8, Escape = 27;
        char S[200];
        char MultimeDeCaractereAcceptabile[200] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+-=*/;? ";
        char Sinitial[200], tasta;
        char Ss[200];

        strcpy(Sinitial,S);
        strcpy(text, Sinitial);
        setlinestyle(0, 0, 2);
        setcolor(1);
        setfillstyle(1,button_color);
        setbkcolor(button_color);
        strcpy(S,"");

        do
        {
            tasta=getch();
            if (tasta==0)
            {
                tasta=getch();
                Beep(200,200);
            }
            else if (strchr(MultimeDeCaractereAcceptabile,tasta))
            {
                // stergem fostul sir
                strcpy(Ss,S);
                strcat(Ss,"_ ");

                strcpy(text, Ss);
                create_button();
                put_text();


                char tt2[2];
                tt2[0]=tasta;
                tt2[1]=0;
                strcat(S,tt2);

                // afisam pe cel nou }
                strcpy(Ss,S);
                strcat(Ss,"_ ");

                strcpy(text, Ss);
                create_button();
                put_text();
            }
            else if (tasta == BackSpace)
            {
                if (!strcmp(S,""))
                    Beep(200,200);
                else
                {
                    strcpy(Ss,S);
                    strcat(Ss,"_");

                    strcpy(text, Ss);
                    create_button();
                    put_text();


                    S[strlen(S)-1]=0;
                    strcpy(Ss,S);
                    strcat(Ss,"_ ");

                    strcpy(text, Ss);
                    create_button();
                    put_text();

                }
            }
            else if (tasta!=Enter && tasta!=Escape)
                Beep(200,200);
        }
        while (tasta!=Enter && tasta!=Escape);

        if (tasta == Escape)
        {
            strcpy(S,Sinitial);
            strcpy(text, S);
        }

        strcpy(sirnou, S);
        strcpy(text, sirnou);

        string changed_text(text);
        updateFilePortion(filename, changed_text, unchanged_text);
    }

};

class if_button : public button {
public:
    int contor_command=0;                              //comanda butoanelor de pe diagrama
    if_button()
    {
        button_color = COLOR(221, 160, 221);
        frame_color = 1;
        width = 1000 +s_in_out;
        height = 50 +s_in_out;
    }
    void create_button()
    {
        setcolor(1);
        setfillstyle(1, button_color);
        setlinestyle(0, 0, 2);
        bar(top, left, bottom, left + height);
        rectangle(top, left, bottom, right);
        outtextxy((top+bottom)/2-textwidth(text)/2, left+height/2-textheight(text)/2, text);
        int mij = (top + bottom) / 2;
        int y1 = left;
        int y2 = left + height;
        line(top, y1, mij, y2);
        line(mij, y2, bottom, y1);
        rectangle(top, left + height, bottom, left + height);

        ///colorare triunghiuri
        //triunghi 1
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
        setfillstyle(1, LIGHTGREEN);
        floodfill(top + 2, y2 - textheight("A") - 1, 1);
        setcolor(1);
        setlinestyle(0, 0, 2);
        setbkcolor(LIGHTGREEN);
        outtextxy(top + 2, y2 - textheight("A") - 1, "A");                 ///punere text triunghi 1

        //triunghi 2
        setfillstyle(1, LIGHTRED);
        floodfill(bottom - textwidth("F") - 1, y2 - textheight("F") - 1, 1);
        setcolor(1);
        setlinestyle(0, 0, 2);
        setbkcolor(LIGHTRED);
        outtextxy(bottom - textwidth("F") -1, y2 - textheight("F") - 1, "F"); ///punere text triunghi 2
    }
    void put_text()
    {
        int x, y;                                   //coordinates of the text where it starts
        setcolor(text_color);                       //we set the text color
        setbkcolor(button_color);                   //we set the background text color
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);   //we set the font, dimension, direction
        text_height = textheight(text);             //we save the height and length only after aplying fonts
        text_length = textwidth(text);
        x = top + width/2 - text_length/2;          //x starts from the x of the button, we add half the width of the button and substract the half the length of the text
        y = left + height/2 - text_height/2;        //y starts from the y of the button, we add half of the height of the button and substract half od the height of the text
        outtextxy(x, y, text);
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(202,118,202);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(221, 160, 221);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            put_text();
            redraw = 0;
        }
    }
    void edit_button()
    {
        string unchanged_text(text);
        char sirnou[MAX];
        char Enter = 13, BackSpace = 8, Escape = 27;
        char S[200];
        char MultimeDeCaractereAcceptabile[200] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+-=*/;? ";
        char Sinitial[200], tasta;
        char Ss[200];

        strcpy(Sinitial,S);
        strcpy(text, Sinitial);
        setlinestyle(0, 0, 2);
        setcolor(1);
        setfillstyle(1,button_color);
        setbkcolor(button_color);
        strcpy(S,"");

        do
        {
            tasta=getch();
            if (tasta==0)
            {
                tasta=getch();
                Beep(200,200);
            }
            else if (strchr(MultimeDeCaractereAcceptabile,tasta))
            {
                // stergem fostul sir
                strcpy(Ss,S);
                strcat(Ss,"_ ");

                strcpy(text, Ss);
                create_button();
                put_text();


                char tt2[2];
                tt2[0]=tasta;
                tt2[1]=0;
                strcat(S,tt2);

                // afisam pe cel nou }
                strcpy(Ss,S);
                strcat(Ss,"_ ");

                strcpy(text, Ss);
                create_button();
                put_text();
            }
            else if (tasta == BackSpace)
            {
                if (!strcmp(S,""))
                    Beep(200,200);
                else
                {
                    strcpy(Ss,S);
                    strcat(Ss,"_");

                    strcpy(text, Ss);
                    create_button();
                    put_text();


                    S[strlen(S)-1]=0;
                    strcpy(Ss,S);
                    strcat(Ss,"_ ");

                    strcpy(text, Ss);
                    create_button();
                    put_text();

                }
            }
            else if (tasta!=Enter && tasta!=Escape)
                Beep(200,200);
        }
        while (tasta!=Enter && tasta!=Escape);

        if (tasta == Escape)
        {
            strcpy(S,Sinitial);
            strcpy(text, S);
        }

        strcpy(sirnou, S);
        strcpy(text, sirnou);

        string changed_text(text);
        updateFilePortion(filename, changed_text, unchanged_text);
    }
};

class while_button : public button {
public:
    int contor_command=0;                              //comanda butoanelor de pe diagrama
    while_button()
    {
        button_color = COLOR(143,188,143);
        frame_color = 1;
        width = 1000;
        height = 50;
    }
    void create_button()
    {
        setcolor(1);
        setbkcolor(button_color);
        setlinestyle(0, 0, 2);
        setfillstyle(1, button_color);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
        bar(top, left, bottom, left + height);
        bar(top, left, top+30, right);
        setcolor(1);
        setbkcolor(button_color);

        //liniile de pe margini
        line(top, left, bottom, left);
        line(top, left, top, right);
        line(top, right, top+30, right);
        line(bottom, left, bottom, right);
        //liniile din interior
        line(top+30, left+height, top+30, right);
        line(top+30, left+height, bottom, left+height);
    }
    void put_text()
    {
        int x, y;                                   //coordinates of the text where it starts
        setcolor(text_color);                       //we set the text color
        setbkcolor(button_color);                   //we set the background text color
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);   //we set the font, dimension, direction
        text_height = textheight(text);             //we save the height and length only after aplying fonts
        text_length = textwidth(text);
        x = top + width/2 - text_length/2;          //x starts from the x of the button, we add half the width of the button and substract the half the length of the text
        y = left + height/2 - text_height/2;        //y starts from the y of the button, we add half of the height of the button and substract half od the height of the text
        outtextxy(x, y, text);
    }
    bool is_inside_button(int x, int y)
    {
        return ((x > top && x < top + width && y > left && y < left + height) || (x > top && x < top + 30 && y > left && y < right));
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(112,164,112);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(143,188,143);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            put_text();
            redraw = 0;
        }
    }
    bool is_inside_button()
    {
        clearmouseclick(WM_LBUTTONDOWN);
        mx = mousex();
        my = mousey();
        return ((mx > top && mx < top + width && my > left && my < left + height) || (mx > top && mx < top + 30 && my > left && my < right));
    }
    void edit_button()
    {
        string unchanged_text(text);
        char sirnou[MAX];
        char Enter = 13, BackSpace = 8, Escape = 27;
        char S[200];
        char MultimeDeCaractereAcceptabile[200] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+-=*/;? ";
        char Sinitial[200], tasta;
        char Ss[200];

        strcpy(Sinitial,S);
        strcpy(text, Sinitial);
        setlinestyle(0, 0, 2);
        setcolor(1);
        setfillstyle(1,button_color);
        setbkcolor(button_color);
        strcpy(S,"");

        do
        {
            tasta=getch();
            if (tasta==0)
            {
                tasta=getch();
                Beep(200,200);
            }
            else if (strchr(MultimeDeCaractereAcceptabile,tasta))
            {
                // stergem fostul sir
                strcpy(Ss,S);
                strcat(Ss,"_ ");

                strcpy(text, Ss);
                create_button();
                put_text();


                char tt2[2];
                tt2[0]=tasta;
                tt2[1]=0;
                strcat(S,tt2);

                // afisam pe cel nou }
                strcpy(Ss,S);
                strcat(Ss,"_ ");

                strcpy(text, Ss);
                create_button();
                put_text();
            }
            else if (tasta == BackSpace)
            {
                if (!strcmp(S,""))
                    Beep(200,200);
                else
                {
                    strcpy(Ss,S);
                    strcat(Ss,"_");

                    strcpy(text, Ss);
                    create_button();
                    put_text();


                    S[strlen(S)-1]=0;
                    strcpy(Ss,S);
                    strcat(Ss,"_ ");

                    strcpy(text, Ss);
                    create_button();
                    put_text();

                }
            }
            else if (tasta!=Enter && tasta!=Escape)
                Beep(200,200);
        }
        while (tasta!=Enter && tasta!=Escape);

        if (tasta == Escape)
        {
            strcpy(S,Sinitial);
            strcpy(text, S);
        }

        strcpy(sirnou, S);
        strcpy(text, sirnou);

        string changed_text(text);
        updateFilePortion(filename, changed_text, unchanged_text);
    }
};

class for_button : public button {
public:
    int contor_command=0;                              //comanda butoanelor de pe diagrama
    for_button()
    {
        button_color = MAGENTA;
        frame_color = 1;
        width = 1000;
        height = 50;
    }
    void create_button()
    {
        setcolor(1);
        setbkcolor(button_color);
        setlinestyle(0, 0, 2);
        setfillstyle(1, button_color);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
        bar(top, left, bottom, left + height);
        bar(top, left, top+30, right);
        setcolor(1);
        setbkcolor(button_color);

        //liniile de pe margini
        line(top, left, bottom, left);
        line(top, left, top, right);
        line(top, right, top+30, right);
        line(bottom, left, bottom, right);
        //liniile din interior
        line(top+30, left+height, top+30, right);
        line(top+30, left+height, bottom, left+height);
    }
    void put_text()
    {
        int x, y;                                   //coordinates of the text where it starts
        setcolor(text_color);                       //we set the text color
        setbkcolor(button_color);                   //we set the background text color
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);   //we set the font, dimension, direction
        text_height = textheight(text);             //we save the height and length only after aplying fonts
        text_length = textwidth(text);
        x = top + width/2 - text_length/2;          //x starts from the x of the button, we add half the width of the button and substract the half the length of the text
        y = left + height/2 - text_height/2;        //y starts from the y of the button, we add half of the height of the button and substract half od the height of the text
        outtextxy(x, y, text);
    }
    bool is_inside_button(int x, int y)
    {
        return ((x > top && x < top + width && y > left && y < left + height) || (x > top && x < top + 30 && y > left && y < right));
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(92,16,92);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = MAGENTA;
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            put_text();
            redraw = 0;
        }
    }
    bool is_inside_button()
    {
        clearmouseclick(WM_LBUTTONDOWN);
        mx = mousex();
        my = mousey();
        return ((mx > top && mx < top + width && my > left && my < left + height) || (mx > top && mx < top + 30 && my > left && my < right));
    }
    void edit_button()
    {
        string unchanged_text(text);
        char sirnou[MAX];
        char Enter = 13, BackSpace = 8, Escape = 27;
        char S[200];
        char MultimeDeCaractereAcceptabile[200] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+-=*/;? ";
        char Sinitial[200], tasta;
        char Ss[200];

        strcpy(Sinitial,S);
        strcpy(text, Sinitial);
        setlinestyle(0, 0, 2);
        setcolor(1);
        setfillstyle(1,button_color);
        setbkcolor(button_color);
        strcpy(S,"");

        do
        {
            tasta=getch();
            if (tasta==0)
            {
                tasta=getch();
                Beep(200,200);
            }
            else if (strchr(MultimeDeCaractereAcceptabile,tasta))
            {
                // stergem fostul sir
                strcpy(Ss,S);
                strcat(Ss,"_ ");

                strcpy(text, Ss);
                create_button();
                put_text();


                char tt2[2];
                tt2[0]=tasta;
                tt2[1]=0;
                strcat(S,tt2);

                // afisam pe cel nou }
                strcpy(Ss,S);
                strcat(Ss,"_ ");

                strcpy(text, Ss);
                create_button();
                put_text();
            }
            else if (tasta == BackSpace)
            {
                if (!strcmp(S,""))
                    Beep(200,200);
                else
                {
                    strcpy(Ss,S);
                    strcat(Ss,"_");

                    strcpy(text, Ss);
                    create_button();
                    put_text();


                    S[strlen(S)-1]=0;
                    strcpy(Ss,S);
                    strcat(Ss,"_ ");

                    strcpy(text, Ss);
                    create_button();
                    put_text();

                }
            }
            else if (tasta!=Enter && tasta!=Escape)
                Beep(200,200);
        }
        while (tasta!=Enter && tasta!=Escape);

        if (tasta == Escape)
        {
            strcpy(S,Sinitial);
            strcpy(text, S);
        }

        strcpy(sirnou, S);
        strcpy(text, sirnou);

        string changed_text(text);
        updateFilePortion(filename, changed_text, unchanged_text);
    }
};


class do_while_button : public button {
public:
    int contor_command=0;                              //comanda butoanelor de pe diagrama
    do_while_button()
    {
        button_color = COLOR(240,230,140);
        frame_color = 1;
        width = 1000;
        height = 50;
    }
    void create_button()
    {
        setfillstyle(1, button_color);
        setlinestyle(0, 0, 2);
        bar(top , left, top + 30, right+height);
        bar(top + 30, right, bottom, right+height);
        setcolor(1);
        setbkcolor(button_color);

        rectangle(top, left, bottom, right+height);
        line(top + 30, right, bottom, right);
        line(top + 30, left, top + 30, right);
    }
    ///coboara textul recursiv
    void put_text()
    {
        int x, y;                                   //coordinates of the text where it starts
        setcolor(text_color);                       //we set the text color
        setbkcolor(button_color);                   //we set the background text color
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);   //we set the font, dimension, direction
        outtextxy((top +bottom)/2-textwidth(text)/2, right+height/2-textheight(text)/2, text);
    }
    bool is_inside_button(int x, int y)
    {
        return ((x > top && x < top + 30 && y > left && y < right + height) || (x > top && x < top + width && y > right && y < right + height));
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(201,192,115);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(240,230,140);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            put_text();
            redraw = 0;
        }
    }
    bool is_inside_button()
    {
        clearmouseclick(WM_LBUTTONDOWN);
        mx = mousex();
        my = mousey();
        return ((mx > top && mx < top + 30 && my > my && my < right + height) || (mx > top && mx < top + width && my > right && my < right + height));
    }
    void edit_button()
    {
        string unchanged_text(text);
        char sirnou[MAX];
        char Enter = 13, BackSpace = 8, Escape = 27;
        char S[200];
        char MultimeDeCaractereAcceptabile[200] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+-=*/;? ";
        char Sinitial[200], tasta;
        char Ss[200];

        strcpy(Sinitial,S);
        strcpy(text, Sinitial);
        setlinestyle(0, 0, 2);
        setcolor(1);
        setfillstyle(1,button_color);
        setbkcolor(button_color);
        strcpy(S,"");

        do
        {
            tasta=getch();
            if (tasta==0)
            {
                tasta=getch();
                Beep(200,200);
            }
            else if (strchr(MultimeDeCaractereAcceptabile,tasta))
            {
                // stergem fostul sir
                strcpy(Ss,S);
                strcat(Ss,"_ ");

                strcpy(text, Ss);
                create_button();
                put_text();


                char tt2[2];
                tt2[0]=tasta;
                tt2[1]=0;
                strcat(S,tt2);

                // afisam pe cel nou }
                strcpy(Ss,S);
                strcat(Ss,"_ ");

                strcpy(text, Ss);
                create_button();
                put_text();
            }
            else if (tasta == BackSpace)
            {
                if (!strcmp(S,""))
                    Beep(200,200);
                else
                {
                    strcpy(Ss,S);
                    strcat(Ss,"_");

                    strcpy(text, Ss);
                    create_button();
                    put_text();


                    S[strlen(S)-1]=0;
                    strcpy(Ss,S);
                    strcat(Ss,"_ ");

                    strcpy(text, Ss);
                    create_button();
                    put_text();

                }
            }
            else if (tasta!=Enter && tasta!=Escape)
                Beep(200,200);
        }
        while (tasta!=Enter && tasta!=Escape);

        if (tasta == Escape)
        {
            strcpy(S,Sinitial);
            strcpy(text, S);
        }

        strcpy(sirnou, S);
        strcpy(text, sirnou);

        string changed_text(text);
        updateFilePortion(filename, changed_text, unchanged_text);
    }
};

class switch_button : public button {
public:
    int contor_command=0;                              //comanda butoanelor de pe diagrama
    int nr_cases;
    switch_button()
    {
        button_color = COLOR(85, 107, 47);
        frame_color = 1;
        width = 1000;
        height = 50;
    }
    void create_button()
    {
        double w = bottom -(bottom-top)/nr_cases - top;

        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
        setcolor(1);                           //culoarea liniei
        setlinestyle(0, 0, 2);                 //dimensiunea liniilor desenate
        setbkcolor(button_color);        //fondul pentru scris

        ///construirediagrama
        rectangle(top, left, bottom, left+height);
        line(top, left,  top + (nr_cases-1)*(bottom-top)/nr_cases, left+height);         //diagonala-stg
        line(top + (nr_cases-1)*(bottom-top)/nr_cases, left+height, bottom, left);       //diagonala-dr
        line(bottom, left, bottom, right);                                          // linie verticala la dreapta

        ///umplere triunghi - conditie
        setfillstyle(1, button_color);
        floodfill(top + (bottom-top)/nr_cases, left + 5, 1);

        n = nr_cases - 1;
        setbkcolor(COLOR(128, 128, 0));
        for(int i = 1; i <= nr_cases; i++)
        {
            ///linie verticala
            line(top+float(i-1)*w/n, right, top+float(i-1)*w/n, left+float(i-1)*float(height)/n);
        }
    }
    void put_text()
    {
        double w = bottom -(bottom-top)/nr_cases - top;
        int x, y;                                   //coordinates of the text where it starts
        setcolor(text_color);                       //we set the text color
        setbkcolor(button_color);                   //we set the background text color
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);   //we set the font, dimension, direction
        text_height = textheight(text);             //we save the height and length only after aplying fonts
        text_length = textwidth(text);
        x = top+w;          //x starts from the x of the button, we add half the width of the button and substract the half the length of the text
        y = left + height/2 - text_height/2;        //y starts from the y of the button, we add half of the height of the button and substract half od the height of the text
        outtextxy(x, y, text);
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(50,63,28);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(85, 107, 47);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            put_text();
            redraw = 0;
        }
    }
    void edit_button()
    {
        string unchanged_text(text);
        char sirnou[MAX];
        char Enter = 13, BackSpace = 8, Escape = 27;
        char S[200];
        char MultimeDeCaractereAcceptabile[200] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+-=*/;? ";
        char Sinitial[200], tasta;
        char Ss[200];

        strcpy(Sinitial,S);
        strcpy(text, Sinitial);
        setlinestyle(0, 0, 2);
        setcolor(1);
        setfillstyle(1,button_color);
        setbkcolor(button_color);
        strcpy(S,"");

        do
        {
            tasta=getch();
            if (tasta==0)
            {
                tasta=getch();
                Beep(200,200);
            }
            else if (strchr(MultimeDeCaractereAcceptabile,tasta))
            {
                // stergem fostul sir
                strcpy(Ss,S);
                strcat(Ss,"_ ");

                strcpy(text, Ss);
                create_button();
                put_text();


                char tt2[2];
                tt2[0]=tasta;
                tt2[1]=0;
                strcat(S,tt2);

                // afisam pe cel nou }
                strcpy(Ss,S);
                strcat(Ss,"_ ");

                strcpy(text, Ss);
                create_button();
                put_text();
            }
            else if (tasta == BackSpace)
            {
                if (!strcmp(S,""))
                    Beep(200,200);
                else
                {
                    strcpy(Ss,S);
                    strcat(Ss,"_");

                    strcpy(text, Ss);
                    create_button();
                    put_text();


                    S[strlen(S)-1]=0;
                    strcpy(Ss,S);
                    strcat(Ss,"_ ");

                    strcpy(text, Ss);
                    create_button();
                    put_text();

                }
            }
            else if (tasta!=Enter && tasta!=Escape)
                Beep(200,200);
        }
        while (tasta!=Enter && tasta!=Escape);

        if (tasta == Escape)
        {
            strcpy(S,Sinitial);
            strcpy(text, S);
        }

        strcpy(sirnou, S);
        strcpy(text, sirnou);

        string changed_text(text);
        updateFilePortion(filename, changed_text, unchanged_text);
    }
};


class rectangle_button : public button{
public:
    rectangle_button(){
        width = 200, height = 100;
        button_color = LIGHTGRAY, frame_color = DARKGRAY, text_color = WHITE;
    }
};

class square_button : public button{
public:
    square_button(){
        width = 50, height = 50;
        button_color = LIGHTGRAY, frame_color = DARKGRAY, text_color = WHITE;
    }
};

class exit_button : public square_button{
public:
    //const char* img = "x.jpg";
    exit_button(){
        button_color = LIGHTRED, frame_color = DARKGRAY, text_color = WHITE;
    }
    void close_program(){
        ok = true;
        closegraph();
        exit(0);
    }
    void open_image()
    {
        readimagefile("x.jpg", top, left, width, height);
    }
    void put_text()
    {
        int x, y;
        setcolor(text_color);
        setbkcolor(button_color);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
        text_height = textheight(text);
        text_length = textwidth(text);
        x = top + width/2 - text_length/2;
        y = left + height/2 - text_height/2;
        outtextxy(x, y, text);
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = RED;
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = LIGHTRED;
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            put_text();
            redraw = 0;
        }
    }
};

class back_button : public button{
public:
    back_button (){
        top = 150, left = 650, bottom = 350, right = 750;
        width = 200, height = 100;
        button_color = COLOR(33,64,95), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(19,47,74);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(33,64,95);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, inapoi[limba]);
            put_text();
            redraw = 0;
        }
    }
};

class zoom_in_button : public button{   //F
public:
    zoom_in_button(){
        top = 150, left = 100, bottom = 200, right = 150;
        width = 50, height = 50;
        button_color = COLOR(33,64,95), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void zoom_in_function();
    void hoover(int MX, int MY){
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(19,47,74);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(33,64,95);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, "+");
            put_text();
            redraw = 0;
        }
    }
};

class zoom_out_button : public button{ //F
public:
    zoom_out_button(){
        top = 270, left = 100, bottom = 320, right = 150;
        width = 50, height = 50;
        button_color = COLOR(33,64,95), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void zoom_out_function();
    void hoover(int MX, int MY){
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(19,47,74);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(33,64,95);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, "-");
            put_text();
            redraw = 0;
        }
    }
};

class scroll_left_button: public button{ //F
public:
    scroll_left_button(){
        top = 150, left = 170, bottom = 200, right = 220;
        width = 50, height = 50;
        button_color = COLOR(33,64,95), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void move_left();
    void hoover(int MX, int MY){
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(19,47,74);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(33,64,95);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, "<");
            put_text();
            redraw = 0;
        }
    }
};

class scroll_right_button: public button{ //F
public:
    scroll_right_button(){
        top = 270, left = 170, bottom = 320, right = 220;
        width = 50, height = 50;
        button_color = COLOR(33,64,95), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void move_right();
    void hoover(int MX, int MY){
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(19,47,74);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(33,64,95);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, ">");
            put_text();
            redraw = 0;
        }
    }
};

class scroll_up_button: public button{ //F
public:
    scroll_up_button(){
        top = 150, left = 240, bottom = 200, right = 290;
        width = 50, height = 50;
        button_color = COLOR(33,64,95), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void move_up();
    void hoover(int MX, int MY){
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(19,47,74);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(33,64,95);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, "^");
            put_text();
            redraw = 0;
        }
    }
};

class scroll_down_button: public button{ //F
public:
    scroll_down_button(){
        top = 270, left = 240, bottom = 320, right = 290;
        width = 50, height = 50;
        button_color = COLOR(33,64,95), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void move_down();
    void hoover(int MX, int MY){
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(19,47,74);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(33,64,95);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, "v");
            put_text();
            redraw = 0;
        }
    }
};

class save_button : public button{
public:
    save_button(){
        top = 150, left = 530, bottom = 350, right = 630;
        width = 200, height = 100;
        button_color = COLOR(33,64,95), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void save_image()
    {
         writeimagefile(NULL, STG, SUSinitial, STG + W, SUS);
         settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
         if(limba == 1) outtextxy(150, 500, "Diagrama a fost descarcata!");
         else outtextxy(150, 500, "The diagram was download!");
    }
    void hoover(int MX, int MY){
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(19,47,74);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(33,64,95);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, saves[limba]);
            put_text();
            redraw = 0;
        }
    }
};


void build_diagram (nod* p, int xDiagram, int &yDiagram, int wDiagram, int hDiagram);
int indexAtr=0, indexDaca=0, indexCtt=0, indexPtr=0, indexRep=0, indexCaz=0;

class diagram_button : public button{
public:
    diagram_button (){
        top = 150, left = 300, bottom = 350, right = 400;
        width = 200, height = 100;
        button_color = COLOR(33,64,95), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void make_diagram()
    {
        indexAtr=0, indexDaca=0, indexCtt=0, indexPtr=0, indexRep=0, indexCaz=0;
        read_input();
        Initializare_nod(a, "{}", 0, -1);
        arbore(n, a);

        setbkcolor(COLOR(100, 155, 187));
        cleardevice();

        zoom_in_button zoom_i;
        zoom_out_button zoom_o;
        back_button bck10;
        scroll_left_button scroll_l;
        scroll_right_button scroll_r;
        scroll_up_button scroll_u;
        scroll_down_button scroll_d;
        save_button save;

        int y = 100 +s_up_down;
        STG = 500 + s_left_right;
        SUSinitial = SUS = y;
        build_diagram(a, 500+s_left_right, SUS, 1000 + s_in_out, 50 + s_in_out);


        bck10.create_button();
        strcpy(bck10.text, inapoi[limba]);
        bck10.put_text();

        //F
        zoom_i.create_button();
        strcpy(zoom_i.text, "+");
        zoom_i.put_text();

        zoom_o.create_button();
        strcpy(zoom_o.text, "-");
        zoom_o.put_text();

        scroll_l.create_button();
        strcpy(scroll_l.text, "<");
        scroll_l.put_text();

        scroll_r.create_button();
        strcpy(scroll_r.text, ">");
        scroll_r.put_text();

        scroll_u.create_button();
        strcpy(scroll_u.text, "^");
        scroll_u.put_text();

        scroll_d.create_button();
        strcpy(scroll_d.text, "v");
        scroll_d.put_text();

        save.create_button();
        strcpy(save.text, saves[limba]);
        save.put_text();

    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(19,47,74);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(33,64,95);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, diagrama[limba]);
            put_text();
            redraw = 0;
        }
    }
};

class presets_button : public button, public initializer{
public:
    presets_button (){
        top = 150, left = 475, bottom = 350, right = 575;
        width = 200, height = 100;
        button_color = COLOR(33,64,95), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void open_presets(){
        system("cod.in");
        fin.clear();
        fin.seekg(0);
        initialize_program();
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(19,47,74);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(33,64,95);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, salvare[limba]);
            put_text();
            redraw = 0;
        }
    }
};

class text_input_button : public button{
public:
    text_input_button (){
        top = 500, left = 250, bottom = 1500, right = 800;
        width = 575, height = 700;
        button_color = COLOR(33,64,95), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
};
///-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class start_button : public rectangle_button{
public:
    void open_program_start()
    {
        setbkcolor(COLOR(100, 155, 187));
        cleardevice();

        diagram_button dgr;
        presets_button pre;
        back_button bck;
        text_input_button ti;


        dgr.create_button();
        strcpy(dgr.text, diagrama[limba]);
        dgr.put_text();

        pre.create_button();
        strcpy(pre.text, salvare[limba]);
        pre.put_text();

        bck.create_button();
        strcpy(bck.text, inapoi[limba]);
        bck.put_text();

        ti.create_button();
        readimagefile("instructiuni.jpg", 550, 300, 1450, 750);
    }
};


class back_info_button: public button{
public:
    back_info_button(){
        width = 200, height = 100;
        top = 50, left = 50, bottom = 250, right = 150;
        button_color = COLOR(160,82,45), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(117,62,35);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(160,82,45);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, inapoi[limba]);
            put_text();
            redraw = 0;
        }
    }
};

class atribuire_button : public button{
public:
    char text_atr[30];
    atribuire_button (){
        width = 200, height = 100;
        top = getmaxwidth()/2 - width/2, left = 100, bottom = getmaxwidth()/2 + width/2, right = 200;
        button_color = COLOR(160,82,45), frame_color = COLOR(255,250,226), text_color = WHITE;
        strcpy (text_atr, sintax_atr[limba]);
    }
    void put_text()
    {
        int x, y;
        setcolor(text_color);
        setbkcolor(button_color);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
        text_height = textheight(text);
        text_length = textwidth(text);
        x = top + width/2 - text_length/2;
        y = left + height/2 - text_height/2;
        outtextxy(x, y, text);
    }
    void sintaxa_atribuire()
    {
        setbkcolor(COLOR(255,228,196));
        cleardevice();

        int x, y;
        setcolor(COLOR(160,82,45));
        settextstyle(10, 4, 8);
        text_length = textwidth(text_atr);
        x = getmaxwidth()/2 - text_length/2;
        y = 200;
        outtextxy(x, y, text_atr);


        x = getmaxwidth()/2 - textwidth("a = <expresie>")/2;
        settextstyle(0, HORIZ_DIR, 5);
        outtextxy(x+50, y+350, "a = <expresie>");
        setlinestyle(1,1,5);
        rectangle(x, y+340, x+660, y+400);


        back_info_button bck;
        bck.create_button();
        strcpy(bck.text, inapoi[limba]);
        bck.put_text();
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(117,62,35);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(160,82,45);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, aatribuire[limba]);
            put_text();
            redraw = 0;
        }
    }
};

class daca_button : public button{
public:
    char text_atr[30];
    daca_button (){
        width = 200, height = 100;
        top = getmaxwidth()/2 - width/2, left = 250, bottom = getmaxwidth()/2 + width/2, right = 350;
        button_color = COLOR(160,82,45), frame_color = COLOR(255,250,226), text_color = WHITE;
        strcpy (text_atr, sintax_daca[limba]);
    }
    void sintaxa_daca()
    {
        setbkcolor(COLOR(255,228,196));
        cleardevice();

        int x, y;
        setcolor(COLOR(160,82,45));
        settextstyle(10, 4, 8);
        text_length = textwidth(text_atr);
        x = getmaxwidth()/2 - text_length/2;
        y = 200;
        outtextxy(x, y, text_atr);


        x = getmaxwidth()/2 - textwidth("daca <expresie> atunci")/2;
        settextstyle(0, HORIZ_DIR, 5);
        outtextxy(x+70, y+250, "daca <expresie> atunci");
        setlinestyle(1,1,5);

        x = getmaxwidth()/2 - textwidth("<expresie>")/2;
        settextstyle(0, HORIZ_DIR, 5);
        outtextxy(x-40, y+350, "<expresie>");
        setlinestyle(1,1,5);

        x = getmaxwidth()/2 - textwidth("altfel <expresie>")/2;
        settextstyle(0, HORIZ_DIR, 5);
        outtextxy(x-120, y+450, "altfel <expresie>");
        setlinestyle(1,1,5);


        rectangle(x-150, y+180, x+820, y+550);


        back_info_button bck;
        bck.create_button();
        strcpy(bck.text, inapoi[limba]);
        bck.put_text();
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(117,62,35);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(160,82,45);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, ddaca[limba]);
            put_text();
            redraw = 0;
        }
    }
};

class pentru_button : public button{
public:
    char text_atr[50];
    pentru_button (){
        width = 200, height = 100;
        top = getmaxwidth()/2 - width/2, left = 400, bottom = getmaxwidth()/2 + width/2, right = 500;
        button_color = COLOR(160,82,45), frame_color = COLOR(255,250,226), text_color = WHITE;
        strcpy (text_atr, sintax_pentru[limba]);
    }
    void sintaxa_pentru()
    {

        setbkcolor(COLOR(255,228,196));
        cleardevice();

        int x, y;
        setcolor(COLOR(160,82,45));
        settextstyle(10, 4, 8);
        text_length = textwidth(text_atr);
        x = getmaxwidth()/2 - text_length/2;
        y = 200;
        outtextxy(x, y, text_atr);

        x = getmaxwidth()/2 - textwidth("Pentru <expresie> executa")/2;
        settextstyle(0, HORIZ_DIR, 5);
        outtextxy(x+70, y+250, "Pentru <expresie> executa");
        setlinestyle(1,1,5);

        rectangle(x+50, y+180, x+1100, y+350);

        back_info_button bck;
        bck.create_button();
        strcpy(bck.text, inapoi[limba]);
        bck.put_text();
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(117,62,35);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(160,82,45);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, ppentru[limba]);
            put_text();
            redraw = 0;
        }
    }
};
class cat_timp_button : public button{
public:
    char text_atr[30];
    cat_timp_button (){
        width = 200, height = 100;
        top = getmaxwidth()/2 - width/2, left = 550, bottom = getmaxwidth()/2 + width/2, right = 650;
        button_color = COLOR(160,82,45), frame_color = COLOR(255,250,226), text_color = WHITE;
        strcpy (text_atr, sintax_cattimp[limba]);
    }
    void put_text()
    {
        int x, y;
        setcolor(text_color);
        setbkcolor(button_color);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
        text_height = textheight(text);
        text_length = textwidth(text);
        x = top + width/2 - text_length/2;
        y = left + height/2 - text_height/2;
        outtextxy(x, y, text);
    }
    void sintaxa_cat_timp()
    {

        setbkcolor(COLOR(255,228,196));
        cleardevice();

        int x, y;
        setcolor(COLOR(160,82,45));
        settextstyle(10, 4, 8);
        text_length = textwidth(text_atr);
        x = getmaxwidth()/2 - text_length/2;
        y = 200;
        outtextxy(x, y, text_atr);

        x = getmaxwidth()/2 - textwidth("cat_timp <expresie> executa")/2;
        settextstyle(0, HORIZ_DIR, 5);
        outtextxy(x+70, y+250, "cat_timp <expresie> executa");
        setlinestyle(1,1,5);

        rectangle(x+50, y+180, x+1180, y+350);

        back_info_button bck;
        bck.create_button();
        strcpy(bck.text, inapoi[limba]);
        bck.put_text();
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(117,62,35);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(160,82,45);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, ccattimp[limba]);
            put_text();
            redraw = 0;
        }
    }
};

class pana_cand_button : public button{
public:
    char text_atr[30];
    pana_cand_button (){
        width = 200, height = 100;
        top = getmaxwidth()/2 - width/2, left = 700, bottom = getmaxwidth()/2 + width/2, right = 800;
        button_color = COLOR(160,82,45), frame_color = COLOR(255,250,226), text_color = WHITE;
        strcpy (text_atr, sintax_panacand[limba]);
    }
    void put_text()
    {
        int x, y;
        setcolor(text_color);
        setbkcolor(button_color);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
        text_height = textheight(text);
        text_length = textwidth(text);
        x = top + width/2 - text_length/2;
        y = left + height/2 - text_height/2;
        outtextxy(x, y, text);
    }
    void sintaxa_pana_cand()
    {
        setbkcolor(COLOR(255,228,196));
        cleardevice();

        int x, y;
        setcolor(COLOR(160,82,45));
        settextstyle(10, 4, 8);
        text_length = textwidth(text_atr);
        x = getmaxwidth()/2 - text_length/2;
        y = 200;
        outtextxy(x, y, text_atr);


        x = getmaxwidth()/2 - textwidth("repeta ")/2;
        settextstyle(0, HORIZ_DIR, 5);
        outtextxy(x-360, y+250, "repeta ");
        setlinestyle(1,1,5);

        x = getmaxwidth()/2 - textwidth("<expresie>")/2;
        settextstyle(0, HORIZ_DIR, 5);
        outtextxy(x-100, y+350, "<expresie>");
        setlinestyle(1,1,5);

        x = getmaxwidth()/2 - textwidth("pana_cand <expresie>")/2;
        settextstyle(0, HORIZ_DIR, 5);
        outtextxy(x-120, y+450, "pana_cand <expresie>");
        setlinestyle(1,1,5);


        rectangle(x-150, y+180, x+820, y+550);


        back_info_button bck;
        bck.create_button();
        strcpy(bck.text, inapoi[limba]);
        bck.put_text();
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(117,62,35);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(160,82,45);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, ppanacand[limba]);
            put_text();
            redraw = 0;
        }
    }
};

class cazuri_button : public button{
public:
    char text_atr[30];
    cazuri_button (){
        width = 200, height = 100;
        top = getmaxwidth()/2 - width/2, left = 850, bottom = getmaxwidth()/2 + width/2, right = 950;
        button_color = COLOR(160,82,45), frame_color = COLOR(255,250,226), text_color = WHITE;
        strcpy (text_atr, sintax_cazuri[limba]);
    }
    void sintaxa_cazuri()
    {
        setbkcolor(COLOR(255,228,196));
        cleardevice();

        int x, y;
        setcolor(COLOR(160,82,45));
        settextstyle(10, 4, 8);
        text_length = textwidth(text_atr);
        x = getmaxwidth()/2 - text_length/2;
        y = 150;
        outtextxy(x, y, text_atr);


        x = getmaxwidth()/2 - textwidth("switch( <expresie> )")/2;
        x+=100;
        settextstyle(0, HORIZ_DIR, 5);
        outtextxy(x, y+250, "switch( <expresie> )");
        setlinestyle(1,1,5);

        x = getmaxwidth()/2 - textwidth("case <i>:")/2;
        x+=100;
        settextstyle(0, HORIZ_DIR, 5);
        outtextxy(x-100, y+350, "case <i>:");
        setlinestyle(1,1,5);

        x = getmaxwidth()/2 - textwidth("<expresie>")/2;
        x+=100;
        settextstyle(0, HORIZ_DIR, 5);
        outtextxy(x, y+450, "<expresie>");
        setlinestyle(1,1,5);

        x = getmaxwidth()/2 - textwidth("default:")/2;
        x+=100;
        settextstyle(0, HORIZ_DIR, 5);
        outtextxy(x-120, y+550, "default:");
        setlinestyle(1,1,5);

        x = getmaxwidth()/2 - textwidth("<expresie>")/2;
        x+=100;
        settextstyle(0, HORIZ_DIR, 5);
        outtextxy(x, y+650, "<expresie>");
        setlinestyle(1,1,5);


        rectangle(x-300, y+180, x+560, y+750);


        back_info_button bck;
        bck.create_button();
        strcpy(bck.text, inapoi[limba]);
        bck.put_text();
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(117,62,35);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(160,82,45);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, ccazuri[limba]);
            put_text();
            redraw = 0;
        }
    }
};


class info_button : public rectangle_button {
public:
    void open_program_info()
    {
        setbkcolor(COLOR(255,228,196));
        cleardevice();

        atribuire_button atb;
        daca_button dc;
        pentru_button pt;
        cat_timp_button ct;
        pana_cand_button pc;
        cazuri_button cz;
        back_info_button bck;

        atb.create_button();
        strcpy(atb.text, aatribuire[limba]);
        atb.put_text();

        dc.create_button();
        strcpy(dc.text, ddaca[limba]);
        dc.put_text();

        pt.create_button();
        strcpy(pt.text, ppentru[limba]);
        pt.put_text();

        ct.create_button();
        strcpy(ct.text, ccattimp[limba]);
        ct.put_text();

        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
        pc.create_button();
        strcpy(pc.text, ppanacand[limba]);
        pc.put_text();

        cz.create_button();
        strcpy(cz.text, ccazuri[limba]);
        cz.put_text();

        bck.create_button();
        strcpy(bck.text, inapoi[limba]);
        bck.put_text();



    }
};

class language_button : public button{
public:
    language_button(){
        width = 200, height = 100;
        top = 850, left = getmaxheight()/2, bottom = top+200, right = left+100;
        button_color = COLOR(85, 107, 47), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void change_language();
    void put_text()
    {
        int x, y;
        setcolor(text_color);
        setbkcolor(button_color);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
        text_height = textheight(text);
        text_length = textwidth(text);
        x = top + width/2 - text_length/2;
        y = left + height/2 - text_height/2;
        outtextxy(x, y, text);
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX,  MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(58,74,31);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(85, 107, 47);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, llimba[limba]);
            put_text();
            redraw = 0;
        }
    }
};

class back_settings_button : public button {
public:
     back_settings_button(){
        width = 200, height = 100;
        top = 850, left = 350, bottom = top+200, right = 450;
        button_color = COLOR(85, 107, 47), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void hoover(int MX, int MY)
    {
        if(is_inside_button(MX, MY) && current_pos==0 && redraw == 0)
        {
            button_color = COLOR(58,74,31);
            redraw = 1;
            current_pos = 1;
        }
        else if(!is_inside_button(MX, MY) && current_pos==1 && redraw == 0)
        {
            button_color = COLOR(85, 107, 47);
            redraw = 1;
            current_pos = 0;
        }
        if(redraw)
        {
            create_button();
            strcpy(text, inapoi[limba]);
            put_text();
            redraw = 0;
        }
    }
};

class settings_button : public rectangle_button{
public:
    void open_program_settings()
    {
        setbkcolor(COLOR(143, 188, 143));
        cleardevice();

        language_button language;
        back_settings_button bck;

        language.create_button();
        strcpy(language.text, llimba[limba]);
        language.put_text();

        bck.create_button();
        strcpy(bck.text, inapoi[limba]);
        bck.put_text();

    }
};

void language_button::change_language()
{
    if(limba == 0)
        limba = 1;
    else
        limba = 0;

    re_initialize_buttons();

    setbkcolor(COLOR(143, 188, 143));
    cleardevice();

    language_button language;
    back_settings_button bck;

    language.create_button();
    strcpy(language.text, llimba[limba]);
    language.put_text();

    bck.create_button();
    strcpy(bck.text, inapoi[limba]);
    bck.put_text();
}



class chat_button : public square_button{
public:
    char input[100];
    void open_chat()
    {
        setbkcolor(COLOR(100, 155, 187));
        cleardevice();

        back_button bck2;
        bck2.create_button();
        strcpy(bck2.text, inapoi[limba]);
        bck2.put_text();

        setbkcolor(COLOR(100, 155, 187));
        int xs = 100, ys = 50; //coordonatele de unde incepe sirul
        char Enter = 13, BackSpace = 8, Escape = 27;
        char MultimeDeCaractereAcceptabile[200] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+-=/*? ";
        char Sinitial[200], tasta;
        char Ss[200];
        char S[200]="";
        char mesaj[200]="";
        strcpy(mesaj, "How can I help you?");
        setbkcolor(COLOR(100, 155, 187));
        setlinestyle(0, 0, 2);
        setfillstyle(1,LIGHTGRAY);
        do
        {
            outtextxy(xs, ys, mesaj);
            ys+=30;
           // strcpy(Sinitial,S);
            strcpy(S,"");

            do
            {
                tasta=getch();
                if (tasta==0)
                {
                    tasta=getch();
                    Beep(200,200);
                }
                else if (strchr(MultimeDeCaractereAcceptabile,tasta))
                {
                    // stergem fostul sir
                    strcpy(Ss,S);
                    strcat(Ss,"_ ");

                    outtextxy(xs,ys,Ss);

                    char tt2[2];
                    tt2[0]=tasta;
                    tt2[1]=0;
                    strcat(S,tt2);

                    // afisam pe cel nou }
                    strcpy(Ss,S);

                    setcolor(WHITE);
                    outtextxy(xs,ys,Ss);

                }
                else if (tasta == BackSpace)
                {
                    if (!strcmp(S,""))
                        Beep(200,200);
                    else
                    {
                        strcpy(Ss,S);
                        strcat(Ss,"_");

                        outtextxy(xs,ys,Ss);
                        setcolor(WHITE);

                        S[strlen(S)-1]=0;
                        strcpy(Ss,S);

                        outtextxy(xs,ys,Ss);

                    }
                }
                else if (tasta!=Enter && tasta!=Escape)
                    Beep(200,200);
            }
            while (tasta!=Enter && tasta!=Escape);

          //  if (tasta == Escape) strcpy(S,Sinitial);


            if(strcmp(S, "How can I use this project?")== 0)
                strcpy(mesaj, "Press the START button then, on the pressets button to introduce your pseudocode.");
            else if(strcmp(S, "exit") == 0)
                strcpy(mesaj, "Nice talking to you. Press any key to exit.");
            else if(strcmp(S, "How to use an if?")== 0 || strcmp(S, "How to use a while?") == 0 || strcmp(S, "How to use a for?") ==0 || strcmp(S, "How to use a switch?") == 0 || strcmp(S, "How to use a do_while?") == 0)
                    strcpy(mesaj, "Please go back and click on the info button to find more about this instruction.");
            else if(strcmp(S, "Thank you")==0 || strcmp(S, "thank you")==0)
                    strcpy(mesaj, "You're welcome!");
            else if(strcmp(S, "hello") == 0 || strcmp(S, "Hello") == 0)
                    strcpy(mesaj, "Hi! How can I help you?");
            else
                strcpy(mesaj, "Sorry. I am not smart enough.");
            ys+=30;
            outtextxy(xs,ys,S);

         }while(strcmp(S, "exit") != 0);
    }
};

    initializer program;
    screen s;

    info_button info;
    settings_button settings;
    start_button start;
    chat_button chat;
    exit_button exitt;

    button* v[10];

    diagram_button diagram;
    presets_button presets;
    back_button bck;
    zoom_in_button zoom_in; //F
    zoom_out_button zoom_out; //F
    scroll_left_button scroll_left; //F
    scroll_right_button scroll_right; //F
    scroll_up_button scroll_up; //F
    scroll_down_button scroll_down; //F
    text_input_button text_input;
    save_button download;

    atribuire_button atribuire;
    daca_button daca;
    pentru_button pentru;
    cat_timp_button cat_timp;
    pana_cand_button pana_cand;
    cazuri_button cazuri;
    back_info_button back_info;

    language_button language;
    back_settings_button back_settings;

    back_button bck2;       //button back pt chat


    /// parte noua
    assign_button atr[100];
    while_button ctt[100];
    for_button ptr[100];
    if_button dac[100];
    do_while_button rep[100];
    switch_button caz[100];
    int xDiagram = 500;


void button::draw_menu()
{
    setbkcolor(BLACK);
    cleardevice();

    //we create the buttons and we put the text inside
    {
        start.create_button();
        info.create_button();
        settings.create_button();
        exitt.create_button();
        chat.create_button();

        start.put_text();
        info.put_text();
        settings.put_text();
        exitt.put_text();
        chat.put_text();
    }
}

void button::search_for_mouse_activity()
{
    bool clicked = false;
    int chosen=0, command = 0;
    static int contor = 28;
    while(!clicked)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            if(curent == 0 && !clicked) ///ecran de start
            {
                if(start.is_inside_button())
                {
                    chosen = 1;
                    clicked = true;
                    curent = 1;
                }
                else if(info.is_inside_button())
                {
                    chosen = 2;
                    clicked = true;
                    curent = 2;
                }
                else if(settings.is_inside_button())
                {
                    chosen = 3;
                    clicked = true;
                    curent = 3;
                }
                else if(chat.is_inside_button())
                {
                    chosen = 4;
                    clicked = true;
                    curent = 6;
                }
                else if(exitt.is_inside_button())
                {
                    chosen = 5;
                    clicked = true;
                    //curent = 0;
                }
            }
            else if(curent == 1 && !clicked)    ///ecran cu diagrama, salvare, inapoi
            {
                if(diagram.is_inside_button())
                {
                    chosen = 6;
                    clicked = true;
                    curent = 4;
                }
                else if(presets.is_inside_button())
                {
                    chosen = 7;
                    clicked = true;
                }
                else if(bck.is_inside_button())
                {
                    chosen = 8;
                    clicked = true;
                    curent = 0;
                }
            }
            else if(curent == 2 && !clicked)    ///ecran cu informatii
            {
                if(atribuire.is_inside_button())
                {
                    chosen = 9;
                    clicked = true;
                    curent = 5;
                }
                else if(daca.is_inside_button())
                {
                    chosen = 10;
                    clicked = true;
                    curent = 5;
                }
                else if(pentru.is_inside_button())
                {
                    chosen = 11;
                    clicked = true;
                    curent = 5;
                }
                else if(cat_timp.is_inside_button())
                {
                    chosen = 12;
                    clicked = true;
                    curent = 5;
                }
                else if(pana_cand.is_inside_button())
                {
                    chosen = 13;
                    clicked = true;
                    curent = 5;
                }
                else if(cazuri.is_inside_button())
                {
                    chosen = 14;
                    clicked = true;
                    curent = 5;
                }
                else if(back_info.is_inside_button())
                {
                    chosen = 15;
                    clicked = true;
                    curent = 0;
                }
            }
            else if(curent == 3 && !clicked)    ///ecran setari
            {
                if(language.is_inside_button())
                {
                    chosen = 16;
                    clicked = true;
                    curent = 3;
                }
                else if(back_settings.is_inside_button())
                {
                    chosen = 17;
                    clicked = true;
                    curent = 0;
                }
            }
            else if(curent == 4 && !clicked)    ///ECRAN CU DIAGRAMA
            {
                if(bck.is_inside_button())
                {
                    chosen = 18;
                    clicked = true;
                    curent = 1;
                }
                else if(zoom_in.is_inside_button())
                {
                    chosen = 19;
                    clicked = true;
                    curent = 4;
                }
                else if(zoom_out.is_inside_button())
                {
                    chosen = 20;
                    clicked = true;
                    curent = 4;
                }
                else if(scroll_left.is_inside_button())
                {
                    chosen = 21;
                    clicked = true;
                    curent = 4;
                }
                else if(scroll_right.is_inside_button())
                {
                    chosen = 22;
                    clicked = true;
                    curent = 4;
                }

                else if(scroll_up.is_inside_button())
                {
                    chosen = 23;
                    clicked = true;
                    curent = 4;
                }
                else if(scroll_down.is_inside_button())
                {
                    chosen = 24;
                    clicked = true;
                    curent = 4;
                }
                else if(download.is_inside_button())
                {
                    //cout << download.top << " " << download.left << " " << download.bottom << " " << download.right << endl;
                    chosen = 25;
                    clicked = true;
                    curent = 4;
                }
                else
                {
                    for(int i=0; i<indexAtr && clicked==false; i++)
                    {
                        if(atr[i].is_inside_button()) //&& atr[i].contor_command==0)
                        {
                            atr[i].contor_command = contor;
                            chosen = contor;
                            clicked = true;
                            curent = 4;


                            contor++;
                        }
                    }
                    for(int i=0; i<indexDaca && clicked==false; i++)
                    {
                        if(dac[i].is_inside_button()) //&& dac[i].contor_command==0)
                        {
                            dac[i].contor_command = contor;
                            chosen = contor;
                            clicked = true;
                            curent = 4;


                            contor++;
                        }
                    }
                    for(int i=0; i<indexCtt && clicked==false; i++)
                    {
                        if(ctt[i].is_inside_button()) //&& ctt[i].contor_command==0)
                        {
                            ctt[i].contor_command = contor;
                            chosen = contor;
                            clicked = true;
                            curent = 4;


                            contor++;
                        }
                    }
                    for(int i=0; i<indexPtr && clicked==false; i++)
                    {
                        if(ptr[i].is_inside_button()) //&& ptr[i].contor_command==0)
                        {
                            ptr[i].contor_command = contor;
                            chosen = contor;
                            clicked = true;
                            curent = 4;


                            contor++;
                        }
                    }
                    for(int i=0; i<indexRep && clicked==false; i++)
                    {
                        if(rep[i].is_inside_button())  //&& rep[i].contor_command==0)
                        {
                            rep[i].contor_command = contor;
                            chosen = contor;
                            clicked = true;
                            curent = 4;


                            contor++;
                        }
                    }
                    for(int i=0; i<indexCaz && clicked==false; i++)
                    {
                        if(caz[i].is_inside_button()) //&& caz[i].contor_command==0)
                        {
                            caz[i].contor_command = contor;
                            chosen = contor;
                            clicked = true;
                            curent = 4;


                            contor++;
                        }
                    }
                }
            }
            else if(curent == 5 && !clicked)            ///ecran la oricare dintre informatiile de instructiuni
            {
                if(back_info.is_inside_button())
                {
                    chosen = 26;
                    clicked = true;
                    curent = 2;
                }
            }
            else if(curent == 6 && !clicked)
            {
                if(bck2.is_inside_button())
                {
                    chosen = 27;
                    clicked = true;
                    curent = 0;
                }
            }
        }
    }
    if(chosen!=0)
    {
        command = chosen;
        if(command == 1)
            start.open_program_start();
        else if(command == 2)
            info.open_program_info();
        else if(command == 3)
            settings.open_program_settings();
        else if(command == 4)
            chat.open_chat();
        else if(command == 5)
            exitt.close_program();
        else if(command == 6)
            diagram.make_diagram();
        else if(command == 7)
            presets.open_presets();
        else if(command == 8)
            bck.draw_menu();
        else if(command == 9)
            atribuire.sintaxa_atribuire();
        else if(command == 10)
            daca.sintaxa_daca();
        else if(command == 11)
            pentru.sintaxa_pentru();
        else if(command == 12)
            cat_timp.sintaxa_cat_timp();
        else if(command == 13)
            pana_cand.sintaxa_pana_cand();
        else if(command == 14)
            cazuri.sintaxa_cazuri();
        else if(command == 15)
            back_info.draw_menu();
        else if(command == 16)
            language.change_language();
        else if(command == 17)
            back_settings.draw_menu();
        else if(command == 18)      /// de la pagina cu diagrama
            start.open_program_start();
        else if(command == 19)
            zoom_in.zoom_in_function();
        else if(command == 20)
            zoom_out.zoom_out_function();
        else if(command == 21)
            scroll_left.move_left();
        else if(command == 22)
            scroll_right.move_right();
        else if(command == 23)
            scroll_up.move_up();
        else if(command == 24)
            scroll_down.move_down();
        else if(command == 25)
            download.save_image();
        else if(command == 26)
            info.open_program_info();
        else if(command == 27)
            bck.draw_menu();
        else if(command >=28)
        {
            //mai pot pune un if care sa verifice tipul de "block" pe care sa il verifice, adica sa stie daca e assign sau while sau etc
            for(int i=0; i<indexAtr; i++)
            {
                if(atr[i].contor_command == command)
                {
                    atr[i].edit_button();
                }
            }
            for(int i=0; i<indexDaca; i++)
            {
                if(dac[i].contor_command == command)
                {
                    dac[i].edit_button();
                }
            }
            for(int i=0; i<indexCtt; i++)
            {
                if(ctt[i].contor_command == command)
                {
                    ctt[i].edit_button();
                }
            }
            for(int i=0; i<indexPtr; i++)
            {
                if(ptr[i].contor_command == command)
                {
                    ptr[i].edit_button();
                }
            }
            for(int i=0; i<indexRep; i++)
            {
                if(rep[i].contor_command == command)
                {
                    rep[i].edit_button();
                }
            }
            for(int i=0; i<indexCaz; i++)
            {
                if(caz[i].contor_command == command)
                {
                    caz[i].edit_button();
                }
            }
        }
    }
}

void initialize_buttons()
{
    s.img="miaumiau.jpg";
    s.open_image();

    strcpy(start.text, incepe[limba]);
    strcpy(info.text, informatii[limba]);
    strcpy(settings.text, setari[limba]);
    strcpy(exitt.text, "X");
    strcpy(chat.text, "?");

    start.top = s.swidth/2 - start.width/2, start.left = s.sheight/4, start.bottom = s.swidth/2 + start.width/2, start.right = s.sheight/4 + start.height;
    info.top = s.swidth/2 - info.width/2, info.left = s.sheight/4 + info.height+70, info.bottom = s.swidth/2 + info.width/2, info.right = s.sheight/4 + 2*info.height + 70;
    settings.top = s.swidth/2 - settings.width/2, settings.left = s.sheight/4 +140 + 2*settings.height, settings.bottom = s.swidth/2 + settings.width/2, settings.right = s.sheight/4 + 3*settings.height +140;

    exitt.top = 50, exitt.left = 50, exitt.bottom = 100, exitt.right = 100;
    chat.top = s.swidth-100, chat.left = s.sheight-100, chat.bottom = s.swidth-50, chat.right = s.sheight-50;

}

void re_initialize_buttons()
{
    strcpy(start.text, incepe[limba]);
    strcpy(info.text, informatii[limba]);
    strcpy(settings.text, setari[limba]);
    strcpy(exitt.text, "X");
    strcpy(chat.text, "?");

    start.top = s.swidth/2 - start.width/2, start.left = s.sheight/4, start.bottom = s.swidth/2 + start.width/2, start.right = s.sheight/4 + start.height;
    info.top = s.swidth/2 - info.width/2, info.left = s.sheight/4 + info.height+70, info.bottom = s.swidth/2 + info.width/2, info.right = s.sheight/4 + 2*info.height + 70;
    settings.top = s.swidth/2 - settings.width/2, settings.left = s.sheight/4 +140 + 2*settings.height, settings.bottom = s.swidth/2 + settings.width/2, settings.right = s.sheight/4 + 3*settings.height +140;

    exitt.top = 50, exitt.left = 50, exitt.bottom = 100, exitt.right = 100;
    chat.top = s.swidth-100, chat.left = s.sheight-100, chat.bottom = s.swidth-50, chat.right = s.sheight-50;

}

void build_diagram (nod* p, int xDiagram, int &yDiagram, int wDiagram, int hDiagram)
{
    for(int i=1; i<=p->nrfii; i++)
    {
        nod *f = p->fii[i];
        if(f->tip == 0) //atribuire
        {
            atr[indexAtr].width = wDiagram;
            atr[indexAtr].height = hDiagram;
            atr[indexAtr].top = xDiagram;
            atr[indexAtr].left = yDiagram;
            atr[indexAtr].bottom = xDiagram + atr[indexAtr].width;
            atr[indexAtr].right = yDiagram + atr[indexAtr].height;

            atr[indexAtr].create_button();
            strcpy(atr[indexAtr].text, f->info+f->nrspatii);
            atr[indexAtr].put_text();

            yDiagram = yDiagram + atr[indexAtr].height;
            indexAtr++;
        }
        else if(f->tip == 1) //daca
        {

            int ystart = yDiagram;
            yDiagram = yDiagram + hDiagram;
            int ycopie = yDiagram;
            int wcopie = wDiagram;

            build_diagram(f, xDiagram, yDiagram, wDiagram/2, hDiagram);
            if(f->indice < p->nrfii && p->fii[i+1]->tip == 2)      //daca este else
                build_diagram(p->fii[i+1], xDiagram + wDiagram/2, ycopie, wDiagram/2, hDiagram);  // ycopie ne intoarcem la inaltimea initiala pentru else
            if(ycopie > yDiagram)
                yDiagram = ycopie;

            dac[indexDaca].width = wDiagram;
            dac[indexDaca].height = hDiagram;
            dac[indexDaca].top = xDiagram;
            dac[indexDaca].left = ystart;
            dac[indexDaca].bottom = xDiagram + dac[indexDaca].width;
            dac[indexDaca].right = yDiagram;

            dac[indexDaca].create_button();
            strncpy(dac[indexDaca].text, f->info + f->nrspatii + strlen("daca "), strlen(f->info + f->nrspatii + strlen("daca "))-strlen(" atunci"));
            dac[indexDaca].text[strlen(f->info + f->nrspatii + strlen("daca "))-strlen(" atunci")] = NULL;
            dac[indexDaca].put_text();

            indexDaca++;

        }
        else if(f->tip == 3) //while
        {
            int ycopie = yDiagram;
            yDiagram+=hDiagram;
            build_diagram(f, xDiagram + 30, yDiagram, wDiagram-30, hDiagram);

            ctt[indexCtt].width = wDiagram;
            ctt[indexCtt].height = hDiagram;
            ctt[indexCtt].top = xDiagram;
            ctt[indexCtt].left = ycopie;
            ctt[indexCtt].bottom = xDiagram + ctt[indexCtt].width;
            ctt[indexCtt].right = yDiagram;

            ctt[indexCtt].create_button();
            strncpy(ctt[indexCtt].text, f->info + f->nrspatii + strlen("cat_timp "), strlen(f->info + f->nrspatii + strlen("cat_timp "))-strlen(" executa"));
            ctt[indexCtt].text[strlen(f->info + f->nrspatii + strlen("cat_timp "))-strlen(" executa")] = NULL;
            ctt[indexCtt].put_text();

            indexCtt++;
        }
        else if(f->tip == 4) //for
        {
            int ycopie = yDiagram;
            yDiagram+=hDiagram;
            build_diagram(f, xDiagram + 30, yDiagram, wDiagram-30, hDiagram);

            ptr[indexPtr].width = wDiagram;
            ptr[indexPtr].height = hDiagram;
            ptr[indexPtr].top = xDiagram;
            ptr[indexPtr].left = ycopie;
            ptr[indexPtr].bottom = xDiagram + ptr[indexPtr].width;
            ptr[indexPtr].right = yDiagram;

            ptr[indexPtr].create_button();
            strncpy(ptr[indexPtr].text, f->info + f->nrspatii + strlen("pentru "), strlen(f->info + f->nrspatii + strlen("pentru "))-strlen(" executa"));
            ptr[indexPtr].text[strlen(f->info + f->nrspatii + strlen("pentru "))-strlen(" executa")] = NULL;
            ptr[indexPtr].put_text();

            indexPtr++;
        }
        else if(f->tip == 5) //switch
        {
            caz[indexCaz].nr_cases = f->nrfii;
            int ycopie = yDiagram;
            int ymax = yDiagram;
            yDiagram+=hDiagram;
            int ycopie2 = yDiagram;
            for(int i = 1; i <= caz[indexCaz].nr_cases; i++)
            {
                build_diagram(f->fii[i], xDiagram + float(i-1)*wDiagram/caz[indexCaz].nr_cases, ycopie2, wDiagram/caz[indexCaz].nr_cases, hDiagram);
                if(ycopie2 > ymax) ymax = ycopie2;
                ycopie2 = yDiagram;
            }

            caz[indexCaz].width = wDiagram;
            caz[indexCaz].height = hDiagram;
            caz[indexCaz].top = xDiagram;
            caz[indexCaz].left = ycopie;
            caz[indexCaz].bottom = xDiagram + caz[indexCaz].width;
            caz[indexCaz].right = ymax;


            caz[indexCaz].create_button();
            strcpy(caz[indexCaz].text, f->info + f->nrspatii + strlen("switch("));
            caz[indexCaz].text[strlen(caz[indexCaz].text)-1]=NULL;
            caz[indexCaz].put_text();
            yDiagram = ymax;

            double w = caz[indexCaz].bottom -(caz[indexCaz].bottom-caz[indexCaz].top)/caz[indexCaz].nr_cases - caz[indexCaz].top;
            setbkcolor(COLOR(128,128,0));
            for(int i = 1; i <= caz[indexCaz].nr_cases; i++)
            {
                ///punere text
                char text[MAX];
                if(strstr(f->fii[i]->info, "case") != 0)
                {
                    strcpy(text, f->fii[i]->info + f->fii[i]->nrspatii + strlen("case "));
                    text[strlen(text)-1] = NULL;
                    setfillstyle(1, COLOR(128, 128, 0));
                    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);


                    ///umplere culoare + text
                    floodfill(caz[indexCaz].top+float(i-1)*w/n+2 , caz[indexCaz].left+caz[indexCaz].height-textheight(text)-1, 1);
                    outtextxy(caz[indexCaz].top+float(i-1)*w/n+2,  caz[indexCaz].left+caz[indexCaz].height-textheight(text)-1, text);
                }
                else
                {
                    strcpy(text, "default:");
                    text[strlen(text)-1]=NULL;
                    setfillstyle(1 ,COLOR(128, 128, 0));
                    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);

                    ///umplere culoare + text
                    floodfill(caz[indexCaz].bottom-10, caz[indexCaz].left+caz[indexCaz].height-textheight(text) , 1);
                    outtextxy(caz[indexCaz].bottom-textwidth(text)-5 , caz[indexCaz].left+caz[indexCaz].height-textheight(text)-1, text);
                }
            }

            indexCaz++;
        }
        else if(f->tip == 6)//do-while
        {

            int ycopie = yDiagram;
            build_diagram(f, xDiagram + 30, yDiagram, wDiagram - 30, hDiagram);


            rep[indexRep].width = wDiagram;
            rep[indexRep].height = hDiagram;
            rep[indexRep].top = xDiagram;
            rep[indexRep].left = ycopie;
            rep[indexRep].bottom = xDiagram + rep[indexRep].width;
            rep[indexRep].right = yDiagram;

            rep[indexRep].create_button();


            ///punere text
            int poz=0;
            for(int i = 1; i <= p->nrfii; i++)
            {
                if(p->fii[i]->tip == 7)
                {
                    poz = i; break;
                }
            }

            strcpy(rep[indexRep].text, p->fii[poz]->info + p->fii[poz]->nrspatii + strlen("pana_cand "));
            rep[indexRep].text[strlen(p->fii[poz]->info)-1] = NULL;
            rep[indexRep].put_text();

            yDiagram+=rep[indexRep].height;
            indexRep++;
        }
    }

}


void zoom_in_button::zoom_in_function()
{
    read_input();
    Initializare_nod(a, "{}", 0, -1);
    arbore(n, a);

    setbkcolor(COLOR(100, 155, 187));
    cleardevice();

    zoom_in_button zoom_i;     //F
    zoom_out_button zoom_o;    //F
    back_button bck10;         //F
    scroll_left_button scroll_l; //F
    scroll_right_button scroll_r; //F
    scroll_up_button scroll_u; //F
    scroll_down_button scroll_d; //F
    save_button down;

    bck10.create_button();
    strcpy(bck10.text, inapoi[limba]);
    bck10.put_text();

    down.create_button();
    strcpy(down.text, saves[limba]);
    down.put_text();

    //F
    zoom_i.create_button();
    strcpy(zoom_i.text, "+");
    zoom_i.put_text();

    zoom_o.create_button();
    strcpy(zoom_o.text, "-");
    zoom_o.put_text();

    scroll_l.create_button();
    strcpy(scroll_l.text, "<");
    scroll_l.put_text();

    scroll_r.create_button();
    strcpy(scroll_r.text, ">");
    scroll_r.put_text();

    scroll_u.create_button();
    strcpy(scroll_u.text, "^");
    scroll_u.put_text();

    scroll_d.create_button();
    strcpy(scroll_d.text, "v");
    scroll_d.put_text();

    indexAtr=0, indexDaca=0, indexCtt=0, indexPtr=0, indexRep=0, indexCaz=0;

    if(s_in_out<50)
        s_in_out+=10;
    int y = 100 +s_up_down;
    STG = 500 + s_left_right;
    SUSinitial = SUS = y;
    W+=s_in_out;

    build_diagram(a, 500 + s_left_right, SUS, 1000 +s_in_out, 50+s_in_out);
}

void zoom_out_button::zoom_out_function()
{
    read_input();
    Initializare_nod(a, "{}", 0, -1);
    arbore(n, a);

    setbkcolor(COLOR(100, 155, 187));
    cleardevice();

    zoom_in_button zoom_i;     //F
    zoom_out_button zoom_o;    //F
    back_button bck10;         //F
    scroll_left_button scroll_l; //F
    scroll_right_button scroll_r; //F
    scroll_up_button scroll_u; //F
    scroll_down_button scroll_d; //F
    save_button down;

    //Is_clicked(); //F

    bck10.create_button();
    strcpy(bck10.text, inapoi[limba]);
    bck10.put_text();

    down.create_button();
    strcpy(down.text, saves[limba]);
    down.put_text();

    //F
    zoom_i.create_button();
    strcpy(zoom_i.text, "+");
    zoom_i.put_text();

    zoom_o.create_button();
    strcpy(zoom_o.text, "-");
    zoom_o.put_text();

    scroll_l.create_button();
    strcpy(scroll_l.text, "<");
    scroll_l.put_text();

    scroll_r.create_button();
    strcpy(scroll_r.text, ">");
    scroll_r.put_text();

    scroll_u.create_button();
    strcpy(scroll_u.text, "^");
    scroll_u.put_text();

    scroll_d.create_button();
    strcpy(scroll_d.text, "v");
    scroll_d.put_text();

    indexAtr=0, indexDaca=0, indexCtt=0, indexPtr=0, indexRep=0, indexCaz=0;

    if(s_in_out>-30)
        s_in_out-=10;
    int y = 100 +s_up_down;
    STG = 500 + s_left_right;
    SUSinitial = SUS = y;
    W+=s_in_out;
    build_diagram(a, 500 + s_left_right, SUS, 1000+s_in_out, 50+s_in_out);

}

void scroll_up_button::move_up()
{
    read_input();
    Initializare_nod(a, "{}", 0, -1);
    arbore(n, a);

    setbkcolor(COLOR(100, 155, 187));
    cleardevice();

    zoom_in_button zoom_i;     //F
    zoom_out_button zoom_o;    //F
    back_button bck10;         //F
    scroll_left_button scroll_l; //F
    scroll_right_button scroll_r; //F
    scroll_up_button scroll_u; //F
    scroll_down_button scroll_d; //F
    save_button down;

    bck10.create_button();
    strcpy(bck10.text, inapoi[limba]);
    bck10.put_text();

    down.create_button();
    strcpy(down.text, saves[limba]);
    down.put_text();

    //F
    zoom_i.create_button();
    strcpy(zoom_i.text, "+");
    zoom_i.put_text();

    zoom_o.create_button();
    strcpy(zoom_o.text, "-");
    zoom_o.put_text();

    scroll_l.create_button();
    strcpy(scroll_l.text, "<");
    scroll_l.put_text();

    scroll_r.create_button();
    strcpy(scroll_r.text, ">");
    scroll_r.put_text();

    scroll_u.create_button();
    strcpy(scroll_u.text, "^");
    scroll_u.put_text();

    scroll_d.create_button();
    strcpy(scroll_d.text, "v");
    scroll_d.put_text();

    indexAtr=0, indexDaca=0, indexCtt=0, indexPtr=0, indexRep=0, indexCaz=0;

    s_up_down -=30;
    int y = 100 +s_up_down;
    STG = 500 + s_left_right;
    SUSinitial = SUS = y;
    build_diagram(a, 500 + s_left_right, SUS, 1000+s_in_out, 50+s_in_out);
}

void scroll_down_button::move_down()
{
    read_input();
    Initializare_nod(a, "{}", 0, -1);
    arbore(n, a);

    setbkcolor(COLOR(100, 155, 187));
    cleardevice();

    zoom_in_button zoom_i;     //F
    zoom_out_button zoom_o;    //F
    back_button bck10;         //F
    scroll_left_button scroll_l; //F
    scroll_right_button scroll_r; //F
    scroll_up_button scroll_u; //F
    scroll_down_button scroll_d; //F
    save_button down;

    bck10.create_button();
    strcpy(bck10.text, inapoi[limba]);
    bck10.put_text();

    down.create_button();
    strcpy(down.text, saves[limba]);
    down.put_text();

    //F
    zoom_i.create_button();
    strcpy(zoom_i.text, "+");
    zoom_i.put_text();

    zoom_o.create_button();
    strcpy(zoom_o.text, "-");
    zoom_o.put_text();

    scroll_l.create_button();
    strcpy(scroll_l.text, "<");
    scroll_l.put_text();

    scroll_r.create_button();
    strcpy(scroll_r.text, ">");
    scroll_r.put_text();

    scroll_u.create_button();
    strcpy(scroll_u.text, "^");
    scroll_u.put_text();

    scroll_d.create_button();
    strcpy(scroll_d.text, "v");
    scroll_d.put_text();

    indexAtr=0, indexDaca=0, indexCtt=0, indexPtr=0, indexRep=0, indexCaz=0;

    s_up_down +=30;
    int y = 100 +s_up_down;
    STG = 500 + s_left_right;
    SUSinitial = SUS = y;
    build_diagram(a, 500 + s_left_right, SUS, 1000+s_in_out, 50+s_in_out);
}

void scroll_right_button::move_right()
{

    read_input();
    Initializare_nod(a, "{}", 0, -1);
    arbore(n, a);

    setbkcolor(COLOR(100, 155, 187));
    cleardevice();

    zoom_in_button zoom_i;     //F
    zoom_out_button zoom_o;    //F
    back_button bck10;         //F
    scroll_left_button scroll_l; //F
    scroll_right_button scroll_r; //F
    scroll_up_button scroll_u; //F
    scroll_down_button scroll_d; //F
    save_button down;

    bck10.create_button();
    strcpy(bck10.text, inapoi[limba]);
    bck10.put_text();

    down.create_button();
    strcpy(down.text, saves[limba]);
    down.put_text();

    //F
    zoom_i.create_button();
    strcpy(zoom_i.text, "+");
    zoom_i.put_text();

    zoom_o.create_button();
    strcpy(zoom_o.text, "-");
    zoom_o.put_text();

    scroll_l.create_button();
    strcpy(scroll_l.text, "<");
    scroll_l.put_text();

    scroll_r.create_button();
    strcpy(scroll_r.text, ">");
    scroll_r.put_text();

    scroll_u.create_button();
    strcpy(scroll_u.text, "^");
    scroll_u.put_text();

    scroll_d.create_button();
    strcpy(scroll_d.text, "v");
    scroll_d.put_text();

    indexAtr=0, indexDaca=0, indexCtt=0, indexPtr=0, indexRep=0, indexCaz=0;
    s_left_right+=30;
    int y = 100 +s_up_down;
    STG = 500 + s_left_right;
    SUSinitial = SUS = y;
    build_diagram(a, 500 + s_left_right, SUS, 1000+s_in_out, 50+s_in_out);

}

void scroll_left_button::move_left()
{
    read_input();
    Initializare_nod(a, "{}", 0, -1);
    arbore(n, a);

    setbkcolor(COLOR(100, 155, 187));
    cleardevice();

    zoom_in_button zoom_i;     //F
    zoom_out_button zoom_o;    //F
    back_button bck10;         //F
    scroll_left_button scroll_l; //F
    scroll_right_button scroll_r; //F
    scroll_up_button scroll_u; //F
    scroll_down_button scroll_d; //F
    save_button down;

    bck10.create_button();
    strcpy(bck10.text, inapoi[limba]);
    bck10.put_text();

    down.create_button();
    strcpy(down.text, saves[limba]);
    down.put_text();

    //F
    zoom_i.create_button();
    strcpy(zoom_i.text, "+");
    zoom_i.put_text();

    zoom_o.create_button();
    strcpy(zoom_o.text, "-");
    zoom_o.put_text();

    scroll_l.create_button();
    strcpy(scroll_l.text, "<");
    scroll_l.put_text();

    scroll_r.create_button();
    strcpy(scroll_r.text, ">");
    scroll_r.put_text();

    scroll_u.create_button();
    strcpy(scroll_u.text, "^");
    scroll_u.put_text();

    scroll_d.create_button();
    strcpy(scroll_d.text, "v");
    scroll_d.put_text();

    indexAtr=0, indexDaca=0, indexCtt=0, indexPtr=0, indexRep=0, indexCaz=0;

    if(s_left_right>-100)
        s_left_right-=30;
    int y = 100+s_up_down;
    STG = 500 + s_left_right;
    SUSinitial = SUS = y;
    build_diagram(a, 500 + s_left_right, SUS, 1000+s_in_out, 50+s_in_out);

}

///a doua functie care nu pune litere in plus la final
void updateFilePortion(const string& filename, const string& newContent, const string& marker)
{
    ifstream inFile(filename, ios::binary);

    if (!inFile.is_open()) {
        cout << "Error: Unable to open file for reading.\n";
        return;
    }

    // Read the file content into a string
    string contentStr((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    size_t markerPos = contentStr.find(marker);

    if (markerPos == string::npos) {
        cout << "Error: Specific portion not found in the file.\n";
        return;
    }

    // Update the line containing the marker
        contentStr.replace(markerPos, marker.length(), newContent);

    ofstream outFile(filename, ios::binary);

    if (!outFile.is_open()) {
        cout << "Error: Unable to open file for writing.\n";
        return;
    }

    // Write the updated content back to the file
    outFile.write(contentStr.c_str(), contentStr.size());
    outFile.flush();

    outFile.close();


    cout << "File portion updated.\n";
}


