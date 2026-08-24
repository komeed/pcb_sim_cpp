/* =========================================================================
 * Base Memory Map Defines
 * ========================================================================= */
#define NRF52840_GPIO_BASE            0x50000000
#define NRF52840_GPIO_P0_BASE         0x50000000
#define NRF52840_GPIO_P1_BASE         0x50000300
#define NRF52840_GPIO_PAGE_SIZE       0x1000

/* Relative Port Offsets */
#define NRF52840_P1_RELATIVE_OFFSET   0x300

/* =========================================================================
 * Relative Register Offsets (Standard for P0 or Normalized Port Operations)
 * ========================================================================= */
#define NRF52840_GPIO_OUT_OFFSET        0x504
#define NRF52840_GPIO_OUTSET_OFFSET     0x508
#define NRF52840_GPIO_OUTCLR_OFFSET     0x50C
#define NRF52840_GPIO_IN_OFFSET         0x510
#define NRF52840_GPIO_DIR_OFFSET        0x514
#define NRF52840_GPIO_DIRSET_OFFSET     0x518
#define NRF52840_GPIO_DIRCLR_OFFSET     0x51C
#define NRF52840_GPIO_LATCH_OFFSET      0x520
#define NRF52840_GPIO_DETECTMODE_OFFSET 0x524
#define NRF52840_GPIO_PIN_CNF_BASE      0x700

/* =========================================================================
 * Explicit Port 0 (P0) Absolute Offsets
 * ========================================================================= */
#define NRF52840_P0_OUT_OFFSET          (NRF52840_GPIO_OUT_OFFSET)
#define NRF52840_P0_OUTSET_OFFSET       (NRF52840_GPIO_OUTSET_OFFSET)
#define NRF52840_P0_OUTCLR_OFFSET       (NRF52840_GPIO_OUTCLR_OFFSET)
#define NRF52840_P0_IN_OFFSET           (NRF52840_GPIO_IN_OFFSET)
#define NRF52840_P0_DIR_OFFSET          (NRF52840_GPIO_DIR_OFFSET)
#define NRF52840_P0_DIRSET_OFFSET       (NRF52840_GPIO_DIRSET_OFFSET)
#define NRF52840_P0_DIRCLR_OFFSET       (NRF52840_GPIO_DIRCLR_OFFSET)
#define NRF52840_P0_LATCH_OFFSET        (NRF52840_GPIO_LATCH_OFFSET)
#define NRF52840_P0_DETECTMODE_OFFSET   (NRF52840_GPIO_DETECTMODE_OFFSET)
#define NRF52840_P0_PIN_CNF_BASE        (NRF52840_GPIO_PIN_CNF_BASE)

/* =========================================================================
 * Explicit Port 1 (P1) Absolute Offsets (Base Offset + 0x300)
 * ========================================================================= */
#define NRF52840_P1_OUT_OFFSET          (NRF52840_GPIO_OUT_OFFSET + NRF52840_P1_RELATIVE_OFFSET) // 0x804
#define NRF52840_P1_OUTSET_OFFSET       (NRF52840_GPIO_OUTSET_OFFSET + NRF52840_P1_RELATIVE_OFFSET) // 0x808
#define NRF52840_P1_OUTCLR_OFFSET       (NRF52840_GPIO_OUTCLR_OFFSET + NRF52840_P1_RELATIVE_OFFSET) // 0x80C
#define NRF52840_P1_IN_OFFSET           (NRF52840_GPIO_IN_OFFSET + NRF52840_P1_RELATIVE_OFFSET) // 0x810
#define NRF52840_P1_DIR_OFFSET          (NRF52840_GPIO_DIR_OFFSET + NRF52840_P1_RELATIVE_OFFSET) // 0x814
#define NRF52840_P1_DIRSET_OFFSET       (NRF52840_GPIO_DIRSET_OFFSET + NRF52840_P1_RELATIVE_OFFSET) // 0x818
#define NRF52840_P1_DIRCLR_OFFSET       (NRF52840_GPIO_DIRCLR_OFFSET + NRF52840_P1_RELATIVE_OFFSET) // 0x81C
#define NRF52840_P1_LATCH_OFFSET        (NRF52840_GPIO_LATCH_OFFSET + NRF52840_P1_RELATIVE_OFFSET) // 0x820
#define NRF52840_P1_DETECTMODE_OFFSET   (NRF52840_GPIO_DETECTMODE_OFFSET + NRF52840_P1_RELATIVE_OFFSET) // 0x824
#define NRF52840_P1_PIN_CNF_BASE        (NRF52840_GPIO_PIN_CNF_BASE + NRF52840_P1_RELATIVE_OFFSET) // 0xA00