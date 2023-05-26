#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    if(((x<0 || x>=im.w) ||(y<0 || y>=im.h)) || (c<0 || c>=im.c))
    {
        return ;
    }
    float *val=im.data + (c*im.w*im.h) + (y*im.w) + x;
    return *val;
}

void set_pixel(image im, int x, int y, int c, float v)
{
    if(((x<0 || x>=im.w) || (y<0 || y>=im.h)) || (c<0 || c>=im.c))
    {
        return;
    }
    im.data[(c*im.w*im.h) + (y*im.w) + x] = v;   
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    for(int i=0; i<(im.w*im.h*im.c); i++)
    {
        copy.data[i] = im.data[i];
    }
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    for(int y=0; y<im.h ; y++)
    {
        for(int x=0; x<im.w; x++)
        {
            float r = get_pixel(im, x, y, 0);
            float g = get_pixel(im, x, y, 1);
            float b = get_pixel(im, x, y, 2);
            float temp = 0.299*r + 0.587*g + 0.114*b;
            set_pixel(gray, x, y, 0, temp);
        }
    }
    return gray;
}

void shift_image(image im, int c, float v)
{
    assert(c>=0 && c<im.c);
    for(int y=0; y<im.h; y++)
    {
        for(int x=0; x<im.w; x++)
        {
            float val = get_pixel(im, x, y, c);
            val=val+v;
            set_pixel(im, x, y, c, val);
        }
    }
}

void clamp_image(image im)
{
    for(int c=0; c<im.c; c++)
    {
        for(int y=0; y<im.h; y++)
        {
            for(int x=0; x<im.w; x++)
            {
                float val = get_pixel(im, x, y, c);
                if(val<0)
                {
                    set_pixel(im, x, y, c, 0);
                }
                else if(val>1)
                {
                    set_pixel(im, x, y, c, 1);
                }
                else
                {
                    set_pixel(im, x, y, c, val);
                }
            }
        }
    }
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    for(int y=0; y<im.h; y++)
    {
        for(int x=0; x<im.w; x++)
        {
            float r = get_pixel(im, x, y, 0);
            float g = get_pixel(im, x, y, 1);
            float b = get_pixel(im, x, y, 2);
            float V = three_way_max(r, g, b);
            float m = three_way_max(r, g, b);
            float C = V-m;
            float s = C/V;
            float h1,h2;
            if(V=0)
            {
                s=0;
            }
            else
            {
                if(V == r)
                {
                    h1 = (g-b)/C;
                }
                else if(V == g)
                {
                    h1 = 2.0 + (b-r)/C;
                }
                else
                {
                    h1 = 4.0 + (r-g)/C;
                }
                if(h1<0)
                {
                    h2 = h1/6 + 1;
                }
                else
                {
                    h2 = h1/6;
                }
                set_pixel(im, x, y, 0, h2);
                set_pixel(im, x, y, 1, s);
                set_pixel(im, x, y, 2, v);
            }
        }
    }
}

void hsv_to_rgb(image im)
{
    for(int y=0; y<im.h; y++)
    {
        for(int x=0; x<im.w; x++)
        {
            float h = get_pixel(im, x, y, 0);
            float s = get_pixel(im, x, y, 1);
            float v = get_pixel(im, x, y, 2);
            
}
