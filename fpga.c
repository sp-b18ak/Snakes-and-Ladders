#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* This files provides address values that exist in the system */

#define BOARD                 "DE1-SoC"

/* Memory */
#define DDR_BASE              0x00000000
#define DDR_END               0x3FFFFFFF
#define A9_ONCHIP_BASE        0xFFFF0000
#define A9_ONCHIP_END         0xFFFFFFFF
#define SDRAM_BASE            0xC0000000
#define SDRAM_END             0xC3FFFFFF
#define FPGA_PIXEL_BUF_BASE   0xC8000000
#define FPGA_PIXEL_BUF_END    0xC803FFFF
#define FPGA_CHAR_BASE        0xC9000000
#define FPGA_CHAR_END         0xC9001FFF

/* Cyclone V FPGA devices */
#define LED_BASE	      0xFF200000
#define LEDR_BASE             0xFF200000
#define HEX3_HEX0_BASE        0xFF200020
#define HEX5_HEX4_BASE        0xFF200030
#define SW_BASE               0xFF200040
#define KEY_BASE              0xFF200050
#define JP1_BASE              0xFF200060
#define JP2_BASE              0xFF200070
#define PS2_BASE              0xFF200100
#define PS2_DUAL_BASE         0xFF200108
#define JTAG_UART_BASE        0xFF201000
#define JTAG_UART_2_BASE      0xFF201008
#define IrDA_BASE             0xFF201020
#define TIMER_BASE            0xFF202000
#define TIMER_2_BASE          0xFF202020
#define AV_CONFIG_BASE        0xFF203000
#define RGB_RESAMPLER_BASE    0xFF203010
#define PIXEL_BUF_CTRL_BASE   0xFF203020
#define CHAR_BUF_CTRL_BASE    0xFF203030
#define AUDIO_BASE            0xFF203040
#define VIDEO_IN_BASE         0xFF203060
#define EDGE_DETECT_CTRL_BASE 0xFF203070
#define ADC_BASE              0xFF204000

/* Cyclone V HPS devices */
#define HPS_GPIO1_BASE        0xFF709000
#define I2C0_BASE             0xFFC04000
#define I2C1_BASE             0xFFC05000
#define I2C2_BASE             0xFFC06000
#define I2C3_BASE             0xFFC07000
#define HPS_TIMER0_BASE       0xFFC08000
#define HPS_TIMER1_BASE       0xFFC09000
#define HPS_TIMER2_BASE       0xFFD00000
#define HPS_TIMER3_BASE       0xFFD01000
#define FPGA_BRIDGE           0xFFD0501C

/* ARM A9 MPCORE devices */
#define   PERIPH_BASE         0xFFFEC000    // base address of peripheral devices
#define   MPCORE_PRIV_TIMER   0xFFFEC600    // PERIPH_BASE + 0x0600

/* Interrupt controller (GIC) CPU interface(s) */
#define MPCORE_GIC_CPUIF      0xFFFEC100    // PERIPH_BASE + 0x100
#define ICCICR                0x00          // offset to CPU interface control reg
#define ICCPMR                0x04          // offset to interrupt priority mask reg
#define ICCIAR                0x0C          // offset to interrupt acknowledge reg
#define ICCEOIR               0x10          // offset to end of interrupt reg
/* Interrupt controller (GIC) distributor interface(s) */
#define MPCORE_GIC_DIST       0xFFFED000    // PERIPH_BASE + 0x1000
#define ICDDCR                0x00          // offset to distributor control reg
#define ICDISER               0x100         // offset to interrupt set-enable regs
#define ICDICER               0x180         // offset to interrupt clear-enable regs
#define ICDIPTR               0x800         // offset to interrupt processor targets regs
#define ICDICFR               0xC00         // offset to interrupt configuration regs

#define EDGE_TRIGGERED 0x1
#define LEVEL_SENSITIVE 0x0
#define CPU0 0x01 // bit-mask; bit 0 represents cpu0
#define ENABLE 0x1

#define KEY0 0
#define KEY1 1
#define NONE 4

#define USER_MODE 0b10000
#define FIQ_MODE 0b10001
#define IRQ_MODE 0b10010
#define SVC_MODE 0b10011
#define ABORT_MODE 0b10111
#define UNDEF_MODE 0b11011
#define SYS_MODE 0b11111

#define INT_ENABLE 0b01000000
#define INT_DISABLE 0b11000000

#define C5 95556
#define D5 85131
#define E5 75843
#define F5 71586
#define G5 63776
#define A5 56818
#define B5 50619
#define C6 47778

/* This file provides interrupt IDs */

/* FPGA interrupts (there are 64 in total; only a few are defined below) */
#define INTERVAL_TIMER_IRQ 72
#define KEYS_IRQ 73
#define FPGA_IRQ2 74
#define FPGA_IRQ3 75
#define FPGA_IRQ4 76
#define FPGA_IRQ5 77
#define FPGA_IRQ6 78
#define FPGA_IRQ7 79
#define JTAG_IRQ 80
#define FPGA_IRQ9 81
#define FPGA_IRQ10 82
#define JP1_IRQ 83
#define JP7_IRQ 84
#define ARDUINO_IRQ 85
#define FPGA_IRQ14 86
#define FPGA_IRQ15 87
#define FPGA_IRQ16 88
#define FPGA_IRQ17 89
#define FPGA_IRQ18 90
#define FPGA_IRQ19 91

/* ARM A9 MPCORE devices (there are many; only a few are defined below) */
#define MPCORE_GLOBAL_TIMER_IRQ 27
#define MPCORE_PRIV_TIMER_IRQ 29
#define MPCORE_WATCHDOG_IRQ 30

/* HPS devices (there are many; only a few are defined below) */
#define HPS_UART0_IRQ 194
#define HPS_UART1_IRQ 195
#define HPS_GPIO0_IRQ 196
#define HPS_GPIO1_IRQ 197
#define HPS_GPIO2_IRQ 198
#define HPS_TIMER0_IRQ 199
#define HPS_TIMER1_IRQ 200
#define HPS_TIMER2_IRQ 201
#define HPS_TIMER3_IRQ 202
#define HPS_WATCHDOG0_IRQ 203
#define HPS_WATCHDOG1_IRQ 204

int ladders[] = {1, 4, 9, 21, 28, 36, 51, 71, 80};
int snakes[] = {16, 47, 49, 56, 62, 64, 87, 93, 95, 98};

extern volatile int tick;
extern volatile int tick2;
// move.c
int nextMove(int);
// board.c
void printBoard(int, int);
// art.c
void printComputerWon();
void printPlayerWon();
// timer.c

void config_GIC(void);
void config_HPS_timer(int);
void config_interval_timer(int);
// music.c
void playTheme(int);
void playTone1();
void playTone2();
void playTone3();
void playToneLadder();
void playToneSnake();
int playerPos;
int cpuPos;
volatile int tick = 0; // set to 1 every time the HPS timer expires
volatile int tick2 = 0;
volatile int key_dir = 0;
volatile int pattern = 0x0F0F0F0F; // pattern for LED lights
volatile int *JP1_ptr = (int *)JP1_BASE;
volatile int *JP2_ptr = (int *)JP2_BASE; // JP2 address
int themeMusic;

void init()
{
    // initialize random seed
    srand(time(0));
    playerPos = 0;
    cpuPos = 0;
}

// Returns a random value between 1 and 6
int rollDice()
{
    return rand() % 6 + 1;
}

void movePlayer(int roll)
{
    int dest;
    dest = nextMove(playerPos + roll);
    playerPos = dest;
    printf("Your position is now %d\n", playerPos);
}

void moveCPU(int roll)
{
    int dest;
    dest = nextMove(cpuPos + roll);
    cpuPos = dest;
    printf("The computer's position is now %d\n", cpuPos);
}

void playerTurn()
{
    int roll;
    volatile int *KEY_ptr = (int *)KEY_BASE;
    int KEY_value = *(KEY_ptr);
    // Player turn
    printf("\nPlease roll dice by pressing one of the push buttons: \n");
    while (KEY_value != 1 && KEY_value != 2 && KEY_value != 4 && KEY_value != 8)
    {
        KEY_value = *(KEY_ptr);
    }
    roll = rollDice();
    printf("You rolled %d\n", roll);
    playRoll(roll);
    movePlayer(roll);
    printBoard(playerPos, cpuPos);
    while (roll == 6)
    {
        KEY_value = *(KEY_ptr);
        printf("You rolled a 6, extra roll!\n");
        printf("\nPlease roll dice by pressing one of the push buttons: \n");
        while (KEY_value != 1 && KEY_value != 2 && KEY_value != 4 && KEY_value != 8)
        {
            KEY_value = *(KEY_ptr);
        }
        roll = rollDice();
        printf("You rolled %d\n", roll);
        playRoll(roll);
        movePlayer(roll);
        printBoard(playerPos, cpuPos);
    }
}

void cpuTurn()
{
    int roll;
    // Computer turn
    roll = rollDice();
    printf("The computer rolled %d\n", roll);
    playRoll(roll);
    moveCPU(roll);
    printBoard(playerPos, cpuPos);
    while (roll == 6)
    {
        printf("The computer rolled a 6, extra roll!\n");
        roll = rollDice();
        printf("The computer rolled %d\n", roll);
        playRoll(roll);
        moveCPU(roll);
        printBoard(playerPos, cpuPos);
    }
}

void welcome()
{
    char playerName[20];
    printf("What is your name? ");
    scanf("%s", &playerName);
    printf("\nHello %s! We're so excited to be with you on this journey. May the best player wins.\n", playerName);
}

int main()
{
    init();
    // Declarations
    int roll;
    // JP1 address
    volatile int *JP1_direction = (int *)0xFF200064; // JP1 direction
    volatile int *JP2_direction = (int *)0xFF200074; // JP2 direction
    volatile int value = 1;
    volatile int value2 = 1;
    *(JP1_direction) = 1;
    *(JP1_ptr) = value;
    *(JP2_direction) = 1;
    *(JP2_ptr) = value2;
    config_GIC();
    config_HPS_timer(C5);
    config_interval_timer(C6);

    welcome();
    selectThemeMusic();

    while (playerPos != 100 && cpuPos != 100)
    {
        playTheme(themeMusic);
        playerTurn();
        playTheme(themeMusic);
        cpuTurn();
    }

    // End of game
    if (playerPos == 100)
    {
        printPlayerWon();
    }
    else if (cpuPos == 100)
    {
        printComputerWon();
    }
    return 0;
}

int nextMove(int dest)
{
    if (dest > 100)
    {
        dest = 100 - (dest - 100);
    }
    switch (dest)
    {
    case 1:
        printf("Woah, first try and you got a ladder!!\n");
        playToneLadder();
        return 38;
    case 4:
        printf("A ladder! Not bad, not bad.\n");
        playToneLadder();
        return 14;
    case 9:
        printf("You've landed on a ladder. Let's hope the good luck stays with you!\n");
        playToneLadder();
        return 31;
    case 16:
        printf("Oh no, a snake ... it's just a small setback.\n");
        playToneSnake();
        return 6;
    case 21:
        printf("A ladder. Keep it up. You got this!!\n");
        playToneLadder();
        return 42;
    case 28:
        printf("You've landed on the biggest ladder in the game. Congratulations!\n");
        playToneLadder();
        return 84;
    case 36:
        printf("A small ladder, we'll take all the wins we can get :)\n");
        playToneLadder();
        return 44;
    case 47:
        printf("You've landed on a snake. Better luck next time.\n");
        playToneSnake();
        return 26;
    case 49:
        printf("Oops, it's a snake. Keep your head up! The game is not over!\n");
        playToneSnake();
        return 11;
    case 51:
        printf("Yesss, go climb that ladder!\n");
        playToneLadder();
        return 67;
    case 56:
        printf("Just a few steps back with this snake, nothing to worry about.\n");
        playToneSnake();
        return 53;
    case 62:
        printf("You've landed on a big snake. Don't give up though.\n");
        playToneSnake();
        return 19;
    case 64:
        printf("You've landed on a small snake, you'll make it up next roll!\n");
        playToneSnake();
        return 60;
    case 71:
        printf("You've made it this far. Another ladder!!\n");
        playToneLadder();
        return 91;
    case 80:
        printf("THE JACKPOT!!! CONGRATULATIONS! You've landed on ladder to the finish line!!!\n");
        playToneLadder();
        return 100;
    case 87:
        printf("Oh no :( Looks like you stepped on the biggest snake in the game... Sorry!\n");
        playToneSnake();
        return 24;
    case 93:
        printf("You got a snake. Don't worry though, if winning was easy it wouldn't feel worth it.\n");
        playToneSnake();
        return 73;
    case 95:
        printf("So close... Yet, so far... Another snake.\n");
        playToneSnake();
        return 75;
    case 98:
        printf("Guess you drew the short straw and got a snake. Don't give up though!\n");
        playToneSnake();
        return 78;
    default:
        return dest;
    }
}

extern volatile int tick;
extern volatile int tick2;
extern volatile int *JP1_ptr;
extern volatile int *JP2_ptr;
extern int themeMusic;

void playPause()
{
    int j = 0;
    int value = 1;
    int value2 = 1;
    for (; j < 2000000; j++)
    {
        if (tick)
        {
            tick = 0;
            *(JP1_ptr) = 0;
        }
        if (tick2)
        {
            tick2 = 0;
            *(JP2_ptr) = 0;
        }
    }
}

void playTone1()
{
    config_HPS_timer(C5);
    config_interval_timer(C6);
    int i = 0;
    int j = 0;
    int value = 1;
    int value2 = 1;
    playPause();
    for (; j < 3; j++)
    {
        for (; i < 1000000; i++)
        {
            if (tick)
            {
                tick = 0;
                *(JP1_ptr) = value;
                value = value == 1 ? 0 : 1;
            }
        }
        for (; i > 0; i--)
        {
            if (tick2)
            {
                tick2 = 0;
                *(JP2_ptr) = value2;
                value2 = value2 == 1 ? 0 : 1;
            }
        }
    }
    playPause();
}

void playTone2()
{
    int i = 0;
    int value = 1;
    int value2 = 1;
    config_HPS_timer(C5);
    playPause();
    for (; i < 1000000; i++)
    {
        if (tick)
        {
            tick = 0;
            *(JP1_ptr) = value;
            value = value == 1 ? 0 : 1;
        }
    }
    config_interval_timer(E5);
    for (; i > 0; i--)
    {
        if (tick2)
        {
            tick2 = 0;
            *(JP2_ptr) = value2;
            value2 = value2 == 1 ? 0 : 1;
        }
    }
    config_HPS_timer(G5);
    for (; i < 1000000; i++)
    {
        if (tick)
        {
            tick = 0;
            *(JP1_ptr) = value;
            value = value == 1 ? 0 : 1;
        }
    }
    playPause();
}

void playTone3()
{
    int i = 0;
    int value = 1;
    int value2 = 1;
    config_HPS_timer(G5);
    playPause();
    for (; i < 1000000; i++)
    {
        if (tick)
        {
            tick = 0;
            *(JP1_ptr) = value;
            value = value == 1 ? 0 : 1;
        }
    }
    config_interval_timer(E5);
    for (; i > 0; i--)
    {
        if (tick2)
        {
            tick2 = 0;
            *(JP2_ptr) = value2;
            value2 = value2 == 1 ? 0 : 1;
        }
    }
    config_HPS_timer(C5);
    for (; i < 1000000; i++)
    {
        if (tick)
        {
            tick = 0;
            *(JP1_ptr) = value;
            value = value == 1 ? 0 : 1;
        }
    }
    playPause();
}

void playTheme(int theme)
{
    switch (theme)
    {
    case 1:
        playTone1();
        break;
    case 2:
        playTone2();
        break;
    case 3:
        playTone3();
        break;
    default:
        playTone2();
    }
}

void playToneLadder()
{
    int i = 0;
    int value = 1;
    int value2 = 1;
    config_HPS_timer(C5);
    for (; i < 1000000; i++)
    {
        if (tick)
        {
            tick = 0;
            *(JP1_ptr) = value;
            value = value == 1 ? 0 : 1;
        }
    }
    config_interval_timer(D5);
    for (; i > 0; i--)
    {
        if (tick2)
        {
            tick2 = 0;
            *(JP2_ptr) = value2;
            value2 = value2 == 1 ? 0 : 1;
        }
    }
    config_HPS_timer(E5);
    for (; i < 1000000; i++)
    {
        if (tick)
        {
            tick = 0;
            *(JP1_ptr) = value;
            value = value == 1 ? 0 : 1;
        }
    }
    config_interval_timer(F5);
    for (; i > 0; i--)
    {
        if (tick2)
        {
            tick2 = 0;
            *(JP2_ptr) = value2;
            value2 = value2 == 1 ? 0 : 1;
        }
    }
    config_HPS_timer(G5);
    for (; i < 1000000; i++)
    {
        if (tick)
        {
            tick = 0;
            *(JP1_ptr) = value;
            value = value == 1 ? 0 : 1;
        }
    }
    config_interval_timer(A5);
    for (; i > 0; i--)
    {
        if (tick2)
        {
            tick2 = 0;
            *(JP2_ptr) = value2;
            value2 = value2 == 1 ? 0 : 1;
        }
    }
    config_HPS_timer(B5);
    for (; i < 1000000; i++)
    {
        if (tick)
        {
            tick = 0;
            *(JP1_ptr) = value;
            value = value == 1 ? 0 : 1;
        }
    }
    config_interval_timer(C6);
    for (; i > 0; i--)
    {
        if (tick2)
        {
            tick2 = 0;
            *(JP2_ptr) = value2;
            value2 = value2 == 1 ? 0 : 1;
        }
    }
}

void playToneSnake()
{
    int i = 0;
    int value = 1;
    int value2 = 1;
    config_HPS_timer(C6);
    for (; i < 1000000; i++)
    {
        if (tick)
        {
            tick = 0;
            *(JP1_ptr) = value;
            value = value == 1 ? 0 : 1;
        }
    }
    config_interval_timer(B5);
    for (; i > 0; i--)
    {
        if (tick2)
        {
            tick2 = 0;
            *(JP2_ptr) = value2;
            value2 = value2 == 1 ? 0 : 1;
        }
    }
    config_HPS_timer(A5);
    for (; i < 1000000; i++)
    {
        if (tick)
        {
            tick = 0;
            *(JP1_ptr) = value;
            value = value == 1 ? 0 : 1;
        }
    }
    config_interval_timer(G5);
    for (; i > 0; i--)
    {
        if (tick2)
        {
            tick2 = 0;
            *(JP2_ptr) = value2;
            value2 = value2 == 1 ? 0 : 1;
        }
    }
    config_HPS_timer(F5);
    for (; i < 1000000; i++)
    {
        if (tick)
        {
            tick = 0;
            *(JP1_ptr) = value;
            value = value == 1 ? 0 : 1;
        }
    }
    config_interval_timer(E5);
    for (; i > 0; i--)
    {
        if (tick2)
        {
            tick2 = 0;
            *(JP2_ptr) = value2;
            value2 = value2 == 1 ? 0 : 1;
        }
    }
    config_HPS_timer(D5);
    for (; i < 1000000; i++)
    {
        if (tick)
        {
            tick = 0;
            *(JP1_ptr) = value;
            value = value == 1 ? 0 : 1;
        }
    }
    config_interval_timer(C5);
    for (; i > 0; i--)
    {
        if (tick2)
        {
            tick2 = 0;
            *(JP2_ptr) = value2;
            value2 = value2 == 1 ? 0 : 1;
        }
    }
}

void playRoll(int count)
{
    int value = 1;
    int value2 = 1;
    int rollCount = 0;
    for (; rollCount < count; rollCount += 1)
    {
        config_HPS_timer(C6);
        config_interval_timer(C5);
        int i = 0;
        for (; i < 1000000; i++)
        {
            if (tick)
            {
                tick = 0;
                *(JP1_ptr) = value;
                value = value == 1 ? 0 : 1;
            }
            if (tick2)
            {
                tick2 = 0;
                *(JP2_ptr) = value2;
                value2 = value2 == 1 ? 0 : 1;
            }
        }
        int j = 0;
        for (; j < 1000000; j++)
        {
            if (tick)
            {
                tick = 0;
                *(JP1_ptr) = 0;
            }
            if (tick2)
            {
                tick2 = 0;
                *(JP2_ptr) = 0;
            }
        }
    }
}

void selectThemeMusic()
{
    themeMusic = 4;
    while (themeMusic != 1 && themeMusic != 2 && themeMusic != 3)
    {
        if (themeMusic < 1 || themeMusic > 4)
        {
            printf("Invalid option, please select one of the options below.");
        }
        printf("Please select a theme music:\n");
        printf("1. Tone 1\n");
        playTone1();
        printf("2. Tone 2\n");
        playTone2();
        printf("3. Tone 3\n");
        playTone3();
        printf("4. Play tones again\n");
        printf("You selected: ");
        scanf("%d", &themeMusic);
    }
}

void printSpace(int step)
{
    if (step == 1 || step == 4 || step == 9 || step == 21 ||
        step == 28 || step == 36 || step == 51 || step == 71 ||
        step == 80)
    {
        printf("L ");
    }
    else if (step == 16 || step == 47 || step == 49 ||
             step == 56 || step == 62 || step == 64 || step == 87 ||
             step == 93 || step == 95 || step == 98)
    {
        printf("S ");
    }
    else
    {
        if (step < 10)
        {
            printf("%d ", step);
        }
        else
        {
            printf("%d", step);
        }
    }
}

void printBox(int i, int player, int cpu)
{
    if (i == player && i == cpu)
    {
        printf(" OX |");
    }
    else if (i == player)
    {
        printf(" O  |");
    }
    else if (i == cpu)
    {
        printf(" X  |");
    }
    else
    {
        if (i == 100)
        {
            printf(" $$ |");
        }
        else
        {
            printf(" ");
            printSpace(i);
            printf(" |");
        }
    }
}

// Increment index
void printRowLR(int i, int player, int cpu)
{
    int threshold = i + 10;
    for (; i < threshold; i += 1)
    {
        printBox(i, player, cpu);
    }
}

// Decrement index
void printRowRL(int i, int player, int cpu)
{
    int threshold = i - 10;
    for (; i > threshold; i -= 1)
    {
        printBox(i, player, cpu);
    }
}

void printBoard(int player, int cpu)
{
    printf(" ---------------------------------------------------\n |");
    printRowRL(100, player, cpu);
    printf("\n ---------------------------------------------------\n |");
    printRowLR(81, player, cpu);
    printf("\n ---------------------------------------------------\n |");
    printRowRL(80, player, cpu);
    printf("\n ---------------------------------------------------\n |");
    printRowLR(61, player, cpu);
    printf("\n ---------------------------------------------------\n |");
    printRowRL(60, player, cpu);
    printf("\n ---------------------------------------------------\n |");
    printRowLR(41, player, cpu);
    printf("\n ---------------------------------------------------\n |");
    printRowRL(40, player, cpu);
    printf("\n ---------------------------------------------------\n |");
    printRowLR(21, player, cpu);
    printf("\n ---------------------------------------------------\n |");
    printRowRL(20, player, cpu);
    printf("\n ---------------------------------------------------\n |");
    printRowLR(1, player, cpu);
    printf("\n ---------------------------------------------------\n");
}

void printComputerWon()
{
    printf("\n\n");
    printf("              ,---------------------------,\n");
    printf("              |  /---------------------\\  |\n");
    printf("              | |                       | |\n");
    printf("              | |       You lost!       | |\n");
    printf("              | |      Better luck      | |\n");
    printf("              | |       next time!      | |\n");
    printf("              | |                       | |\n");
    printf("              |  \\_____________________/  |\n");
    printf("              |___________________________|\n");
    printf("            ,---\\_____     []     _______/------,\n");
    printf("          /         /______________\\           /|\n");
    printf("        /___________________________________ /  | ___\n");
    printf("        |                                   |   |    )\n");
    printf("        |  _ _ _                 [-------]  |   |   (\n");
    printf("        |  o o o                 [-------]  |  /    _)_\n");
    printf("        |__________________________________ |/     /  /\n");
    printf("    /-------------------------------------/|      ( )/\n");
    printf("  /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ /\n");
    printf("/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ /\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n\n");
}

void printPlayerWon()
{
    printf("\n\n");
    printf(" __    __   ______   __    __        __   __   __   ______   _______  \n");
    printf("/  |  /  | /      \\ /  |  /  |      /  | /  | /  | /      \\ /       \\ \n");
    printf("$$ |  $$ |/$$$$$$  |$$ |  $$ |      $$ | $$ | $$ |/$$$$$$  |$$$$$$$  |\n");
    printf("$$ |  $$ |$$ |  $$ |$$ |  $$ |      $$ | $$ | $$ |$$ |  $$ |$$ |  $$ |\n");
    printf("$$ \\__$$ |$$ \\__$$ |$$ \\__$$ |      $$ \\_$$ \\_$$ |$$ \\__$$ |$$ |  $$ |\n");
    printf("$$    $$ |$$    $$/ $$    $$/       $$   $$   $$/ $$    $$/ $$ |  $$ |\n");
    printf(" $$$$$$$ | $$$$$$/   $$$$$$/         $$$$$/$$$$/   $$$$$$/  $$/   $$/ \n");
    printf("/  \\__$$ |                                                            \n");
    printf("$$    $$/                                                             \n");
    printf(" $$$$$$/  \n");
    printf("\n\n");
}

void HPS_timer_ISR()
{
    volatile int *HPS_timer_ptr = (int *)HPS_TIMER0_BASE; // HPS timer address

    ++tick; // used by main program

    *(HPS_timer_ptr + 3); // Read timer end of interrupt register to
                          // clear the interrupt
    return;
}

void interval_timer_ISR()
{
    volatile int *interval_timer_ptr = (int *)TIMER_BASE;
    *(interval_timer_ptr) = 0; // Clear the interrupt

    ++tick2; // used by main program
    return;
}

void config_HPS_timer(int counter)
{
    // timer 0
    volatile int *HPS_timer_ptr = (int *)HPS_TIMER0_BASE; // timer base address

    *(HPS_timer_ptr + 0x2) = 0; // write to control register to stop timer
    *(HPS_timer_ptr) = counter; // write to timer load register

    /* write to control register to start timer, with interrupts */
    *(HPS_timer_ptr + 2) = 0b011; // int mask = 0, mode = 1, enable = 1
}

/* setup the interval timer interrupts in the FPGA */
void config_interval_timer(int counter)
{
    volatile int *interval_timer_ptr =
        (int *)TIMER_BASE; // interal timer base address

    *(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
    *(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;

    /* start interval timer, enable its interrupts */
    *(interval_timer_ptr + 1) = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1
}

void config_GIC(void)
{
    int address; // used to calculate register addresses

    /* configure the HPS timer interrupt */
    *((int *)0xFFFED8C4) = 0x01000000;
    *((int *)0xFFFED118) = 0x00000080;

    /* configure the FPGA interval timer and KEYs interrupts */
    *((int *)0xFFFED848) = 0x00000101;
    *((int *)0xFFFED108) = 0x00000300;

    // Set Interrupt Priority Mask Register (ICCPMR). Enable interrupts of all
    // priorities
    address = MPCORE_GIC_CPUIF + ICCPMR;
    *((int *)address) = 0xFFFF;

    // Set CPU Interface Control Register (ICCICR). Enable signaling of
    // interrupts
    address = MPCORE_GIC_CPUIF + ICCICR;
    *((int *)address) = ENABLE;

    // Configure the Distributor Control Register (ICDDCR) to send pending
    // interrupts to CPUs
    address = MPCORE_GIC_DIST + ICDDCR;
    *((int *)address) = ENABLE;
}