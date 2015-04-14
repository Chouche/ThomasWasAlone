#ifndef COLOR3F_H_
#define COLOR3F_H_

typedef struct {
    float r, g, b;
} Color3f;

Color3f ColorRGB(float r, float g, float b);

extern Color3f BLACK, WHITE, RED, GREEN, BLUE;

#endif
