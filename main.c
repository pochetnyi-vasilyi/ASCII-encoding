#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int main()
{
    int i,j,n,u;
    char c,u1,u2;
    wchar_t uni[386];
    FILE *f1, *f2, *f3;

    if((f2=fopen("result/win1251.txt","w"))==NULL)
    {
        puts("Cannot open file: win1251.txt");
        exit(1);
    }
    if((f3=fopen("result/utf8.txt","w"))==NULL)
    {
        puts("Cannot open file: utf8.txt");
        exit(1);
    }
    for(i=0; i<3; i++)
    {
        if(i==0)
            if((f1=fopen("source/sample 1.txt","r"))==NULL)
            {
                puts("Cannot open file: sample 1");
                exit(1);
            }
        if(i==1)
            if((f1=fopen("source/sample 2.txt","r"))==NULL)
            {
                puts("Cannot open file: sample 2");
                exit(1);
            }
        if(i==2)
            if((f1=fopen("source/sample 3.txt","r"))==NULL)
            {
                puts("Cannot open file: sample 3");
                exit(1);
            }
        c=fgetc(f1);
        fseek(f1,0,SEEK_END);
        n=ftell(f1)-1;
        fseek(f1,0,SEEK_SET);

        unsigned char *s=(unsigned char*)calloc(1,n);
        fread(s,sizeof(unsigned char),n,f1);

        if(i == 0)
        {
            for(j=0; j<n; j++)
            {
                if ((s[j]>=128)&&(s[j]<=175))
                {
                    s[j]+=64;
                    continue;
                }
                if ((s[j]>=224)&&(s[j]<=239))
                {
                    s[j]+=16;
                    continue;
                }
                if (s[j]==240)
                {
                    s[j]=168;
                    continue;
                }
                if (s[j]==241)
                {
                    s[j]=184;
                    continue;
                }
            }
        }
        if((i==1) || (i==2))
        {
            for(j=0; j<n; j++)
            {
                if ((s[j]>=176) && (s[j]<=239))
                {
                    s[j]+=16;
                    continue;
                }
                if (s[j]==161)
                {
                    s[j]=168;
                    continue;
                }
                if (s[j]==241)
                {
                    s[j]=184;
                    continue;
                }
            }
        }
        fputs(s,f2);
        fputs("\n\n",f2);

        wchar_t  win[] =
        {
            0x0402, 0x0403, 0x201A, 0x0453, 0x201E, 0x2026, 0x2020, 0x2021, 0x20AC, 0x2030,0x0409, 0x2039, 0x040A, 0x040C, 0x040B, 0x040F, 0x0452, 0x2018, 0x2019, 0x201C,
            0x201D, 0x2022, 0x2013, 0x2014, 0x0000, 0x2122, 0x0459, 0x203A, 0x045A, 0x045C,0x045B, 0x045F, 0x00A0, 0x040E, 0x045E, 0x0408, 0x00A4, 0x0490, 0x00A6, 0x00A7,
            0x0401, 0x00A9, 0x0404, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x0407, 0x00B0, 0x00B1,0x0406, 0x0456, 0x0491, 0x00B5, 0x00B6, 0x00B7, 0x0451, 0x2166, 0x0254, 0x00BB,
            0x0458, 0x0405, 0x0455, 0x0457, 0x0410, 0x0411, 0x0412, 0x0413, 0x0414, 0x0415,0x0416, 0x0417, 0x0418, 0x0419, 0x041A, 0x041B, 0x041C, 0x041D, 0x041E, 0x041F,
            0x0420, 0x0421, 0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427, 0x0428, 0x0429,0x042A, 0x042B, 0x042C, 0x042D, 0x042E, 0x042F, 0x0430, 0x0431, 0x0432, 0x0433,
            0x0434, 0x0435, 0x0436, 0x0437, 0x0438, 0x0439, 0x043A, 0x043B, 0x043C, 0x043D,0x043E, 0x043F, 0x0440, 0x0441, 0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447,
            0x0448, 0x0449, 0x044A, 0x044B, 0x044C, 0x044D, 0x044E, 0x044F
        };
        u = 0;
        fputc (239, f3);
        fputc (187, f3);
        fputc (191, f3);
        while(u < n)
        {
            if(s[u]<128)
            {
                uni[u]=s[u];
                u++;
                continue;
            }
            uni[u]=win[s[u]-128];
            u++;
        }
        u = 0;
        while(u<n)
        {
            if(uni[u]<128)
                fputc(uni[u],f3);
            else
            {
                u1=192|((1984&uni[u])>>6);
                u2=128|(63&uni[u]);
                fputc(u1,f3);
                fputc(u2,f3);
            }
            u++;
        }

        fclose(f1);
        fputs("\n\n",f3);
    }

    fclose(f2);
    fclose(f3);
    puts("The End!");
    return 0;
}
