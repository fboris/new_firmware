/* #include "stm32f4_flash.h" */

#ifndef __STM32F4_FLASH_H
#define __STM32F4_FLASH_H

#include "stm32f4xx.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define FLASH_SECTOR_0          ((u32)0x08000000) /* Sector 0,   16 Kbytes */
#define FLASH_SECTOR_1          ((u32)0x08004000) /* Sector 1,   16 Kbytes */
#define FLASH_SECTOR_2          ((u32)0x08008000) /* Sector 2,   16 Kbytes */
#define FLASH_SECTOR_3          ((u32)0x0800C000) /* Sector 3,   16 Kbytes */
#define FLASH_SECTOR_4          ((u32)0x08010000) /* Sector 4,   64 Kbytes */
#define FLASH_SECTOR_5          ((u32)0x08020000) /* Sector 5,  128 Kbytes */
#define FLASH_SECTOR_6          ((u32)0x08040000) /* Sector 6,  128 Kbytes */
#define FLASH_SECTOR_7          ((u32)0x08060000) /* Sector 7,  128 Kbytes */
#define FLASH_SECTOR_8          ((u32)0x08080000) /* Sector 8,  128 Kbytes */
#define FLASH_SECTOR_9          ((u32)0x080A0000) /* Sector 9,  128 Kbytes */
#define FLASH_SECTOR_10         ((u32)0x080C0000) /* Sector 10, 128 Kbytes */
#define FLASH_SECTOR_11         ((u32)0x080E0000) /* Sector 11, 128 Kbytes */

#define FLASH_START_ADDR        ((u32)0x08000000)
#define FLASH_PAGE_SIZE         ((u16)0x0400)   // 1KBytes
#define FLASH_PAGE_ADDR(PAGE)   ((u32)(FLASH_START_ADDR + FLASH_PAGE_SIZE*(PAGE)))
/*=====================================================================================================*/
/*=====================================================================================================*/
void Flash_WritePageU8(u32 WritePage, uc8 *WriteData, u32 DataLen);
void Flash_WritePageU16(u32 WritePage, uc16 *WriteData, u32 DataLen);
void Flash_WritePageU32(u32 WritePage, uc32 *WriteData, u32 DataLen);
void Flash_ReadPageU8(u32 ReadPage, u8 *ReadData, u32 DataLen);
void Flash_ReadPageU16(u32 ReadPage, u16 *ReadData, u32 DataLen);
void Flash_ReadPageU32(u32 ReadPage, u32 *ReadData, u32 DataLen);
void Flash_ErasePage(u32 ErasePage);
void Flash_ErasePages(u32 ErasePageStart, u32 ErasePageEnd);
/*=====================================================================================================*/
/*=====================================================================================================*/
#endif
