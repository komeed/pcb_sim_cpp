#define GPIO_OUTSET (*(volatile unsigned int *)0x50000508)

int main(void)
{
    GPIO_OUTSET = 1 << 13;

    while (1);
}