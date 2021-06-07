#include <Arduino.h>

uint16_t static cica[] = {
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0010 (16) pixels
0x0000, 0x0000, 0x0000, 0x0020, 0x5A60, 0xB560, 0xBEA0, 0x9F00, 0x66C0, 0x2D60, 0x0280, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0020 (32) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0030 (48) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0040 (64) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0050 (80) pixels
0x0000, 0x0000, 0x2860, 0xC3A0, 0xFEA0, 0xFFE0, 0xE7E0, 0xB7E0, 0x77E0, 0x3FE0, 0x17E0, 0x0561, 0x00A0, 0x0000, 0x0000, 0x0000,   // 0x0060 (96) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0070 (112) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0080 (128) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0090 (144) pixels
0x0000, 0x2020, 0xDA80, 0xFCC0, 0xFEA0, 0xFFC0, 0xB640, 0x7D60, 0x5E00, 0x3FC0, 0x17E0, 0x07E1, 0x0605, 0x0080, 0x0000, 0x0000,   // 0x00A0 (160) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x00B0 (176) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x00C0 (192) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x00D0 (208) pixels
0x0000, 0xB0C0, 0xFAE0, 0xFCC0, 0xD560, 0x39C0, 0x0020, 0x0000, 0x0000, 0x09A0, 0x0DE0, 0x07E1, 0x07E6, 0x0243, 0x0000, 0x0000,   // 0x00E0 (224) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0067, 0x002F, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8002,   // 0x00F0 (240) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0100 (256) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0110 (272) pixels
0x3800, 0xF920, 0xFAE0, 0xE440, 0x20E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0040, 0x03C0, 0x0443, 0x00A1, 0x0000, 0x0000,   // 0x0120 (288) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0089, 0x007F, 0x000E, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x9007, 0xF805,   // 0x0130 (304) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0140 (320) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0150 (336) pixels
0x8000, 0xF920, 0xFAE0, 0x7A60, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0160 (352) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0088, 0x007F, 0x101F, 0x1009, 0x0000, 0x1004, 0x2004, 0x1002, 0x0000, 0x7009, 0xF80C, 0xF004,   // 0x0170 (368) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0180 (384) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0190 (400) pixels
0xA800, 0xF920, 0xFAE0, 0x4960, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x01A0 (416) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0088, 0x007F, 0x101F, 0x301E, 0x581A, 0x981D, 0xC81E, 0xE01D, 0xC816, 0xF814, 0xF80C, 0xF004,   // 0x01B0 (432) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x01C0 (448) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x01D0 (464) pixels
0xA800, 0xF920, 0xFAE0, 0x5180, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x01E0 (480) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0088, 0x007F, 0x101F, 0x381F, 0x681F, 0xA01F, 0xD01F, 0xF81F, 0xF81C, 0xF814, 0xF80C, 0xE804,   // 0x01F0 (496) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0200 (512) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0210 (528) pixels
0x9000, 0xF920, 0xFAE0, 0x9AE0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0220 (544) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0088, 0x007F, 0x101F, 0x381F, 0x681F, 0xA01F, 0xD01F, 0xF81F, 0xF81C, 0xF814, 0xF80C, 0xE804,   // 0x0230 (560) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0240 (576) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0250 (592) pixels
0x5000, 0xF920, 0xFAE0, 0xF4A0, 0x41A0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0260 (608) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0088, 0x007F, 0x101F, 0x180E, 0x1807, 0x881A, 0xD01F, 0xB017, 0x3005, 0x980C, 0xF80C, 0xE004,   // 0x0270 (624) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0280 (640) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0290 (656) pixels
0x0800, 0xD900, 0xFAE0, 0xFCC0, 0xE5E0, 0x4A60, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x02A0 (672) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0067, 0x007F, 0x081E, 0x0003, 0x0000, 0x6814, 0xD01F, 0x780F, 0x0000, 0x4806, 0xF80C, 0xC804,   // 0x02B0 (688) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x02C0 (704) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x02D0 (720) pixels
0x0000, 0x5860, 0xFAE0, 0xFCC0, 0xFEA0, 0xFFE0, 0xB660, 0x6CC0, 0x3C40, 0x2440, 0x0C40, 0x0440, 0x0443, 0x0446, 0x044A, 0x044D,   // 0x02E0 (736) pixels
0x0450, 0x03F1, 0x0311, 0x01F0, 0x0155, 0x007F, 0x101F, 0x2818, 0x4013, 0xA01E, 0xD01F, 0xE01D, 0x9010, 0xD812, 0xF80C, 0x9003,   // 0x02F0 (752) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0300 (768) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0310 (784) pixels
0x0000, 0x0000, 0x91A0, 0xFCC0, 0xFEA0, 0xFFE0, 0xE7E0, 0xB7E0, 0x77E0, 0x3FE0, 0x17E0, 0x07E1, 0x07E6, 0x07EC, 0x07F3, 0x07FA,   // 0x0320 (800) pixels
0x07FE, 0x075F, 0x05BF, 0x03DF, 0x01FF, 0x007F, 0x101F, 0x381F, 0x681F, 0xA01F, 0xD01F, 0xF81F, 0xF81C, 0xF814, 0xF80C, 0x4001,   // 0x0330 (816) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0340 (832) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0350 (848) pixels
0x0000, 0x0000, 0x0000, 0x7A40, 0xEE00, 0xFFE0, 0xE7E0, 0xB7E0, 0x77E0, 0x3FE0, 0x17E0, 0x07E1, 0x07E6, 0x07EC, 0x07F3, 0x07FA,   // 0x0360 (864) pixels
0x07FE, 0x075F, 0x05BF, 0x03DF, 0x01FF, 0x007F, 0x101F, 0x381F, 0x681F, 0xA01F, 0xD01F, 0xF81F, 0xF81C, 0xF814, 0xC009, 0x0000,   // 0x0370 (880) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0380 (896) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0390 (912) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x20E0, 0x9460, 0xD760, 0xB7E0, 0x77E0, 0x3FE0, 0x17E0, 0x07E1, 0x07E6, 0x07EC, 0x07F3, 0x07FA,   // 0x03A0 (928) pixels
0x07FE, 0x075F, 0x05BF, 0x03DF, 0x01FF, 0x007F, 0x101F, 0x381F, 0x681F, 0xA01F, 0xD01F, 0xF81F, 0xF81C, 0xF814, 0x3802, 0x0000,   // 0x03B0 (944) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x03C0 (960) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x03D0 (976) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8D00, 0xB7E0, 0x77E0, 0x3FE0, 0x17E0, 0x07E1, 0x07E6, 0x07EC, 0x07F3, 0x07FA,   // 0x03E0 (992) pixels
0x07FE, 0x075F, 0x05BF, 0x03DF, 0x01FF, 0x007F, 0x101F, 0x381F, 0x681F, 0xA01F, 0xD01F, 0xF81F, 0xF81C, 0x800A, 0x0000, 0x0000,   // 0x03F0 (1008) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0400 (1024) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0410 (1040) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x9D80, 0xB7E0, 0x77E0, 0x3FE0, 0x17E0, 0x07E1, 0x07E6, 0x07EC, 0x07F3, 0x07FA,   // 0x0420 (1056) pixels
0x07FE, 0x075F, 0x05BF, 0x03DF, 0x01FF, 0x007F, 0x101F, 0x381F, 0x681F, 0xA01F, 0xD01F, 0xF81F, 0xB013, 0x0000, 0x0000, 0x0000,   // 0x0430 (1072) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0440 (1088) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0450 (1104) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0xBE80, 0xB7E0, 0x77E0, 0x3FE0, 0x17E0, 0x07E1, 0x07E6, 0x07EC, 0x07F3, 0x07FA,   // 0x0460 (1120) pixels
0x07FE, 0x075F, 0x05BF, 0x03DF, 0x01FF, 0x007F, 0x101F, 0x381F, 0x681F, 0xA01F, 0xD01F, 0xE81D, 0x2003, 0x0000, 0x0000, 0x0000,   // 0x0470 (1136) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0480 (1152) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0490 (1168) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2960, 0xDFC0, 0xB7E0, 0x77E0, 0x3FE0, 0x17E0, 0x07E1, 0x07E6, 0x07EC, 0x07F3, 0x07FA,   // 0x04A0 (1184) pixels
0x07FE, 0x075F, 0x05BF, 0x03DF, 0x01FF, 0x007F, 0x101F, 0x381F, 0x681F, 0xA01F, 0xD01F, 0xB017, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x04B0 (1200) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x04C0 (1216) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x04D0 (1232) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x9460, 0xE7E0, 0xB7E0, 0x77E0, 0x3FE0, 0x17E0, 0x07E1, 0x07E6, 0x07EC, 0x07F3, 0x07FA,   // 0x04E0 (1248) pixels
0x07FE, 0x075F, 0x05BF, 0x03DF, 0x01FF, 0x007F, 0x101F, 0x381F, 0x681F, 0xA01F, 0xD01F, 0xA816, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x04F0 (1264) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0500 (1280) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0510 (1296) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x20E0, 0xF760, 0xE7E0, 0xB7E0, 0x77E0, 0x3FE0, 0x17E0, 0x07E1, 0x07E6, 0x07EC, 0x07F3, 0x07FA,   // 0x0520 (1312) pixels
0x07FE, 0x075F, 0x05BF, 0x03DF, 0x01FF, 0x007F, 0x101F, 0x381F, 0x681F, 0xA01F, 0xD01F, 0xB016, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0530 (1328) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0540 (1344) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0550 (1360) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0xAC60, 0xFFE0, 0xE7E0, 0xB7E0, 0x77E0, 0x3FE0, 0x17E0, 0x07E1, 0x07E6, 0x05C9, 0x0245, 0x02C9,   // 0x0560 (1376) pixels
0x034C, 0x036F, 0x02AF, 0x01AE, 0x00CD, 0x002D, 0x000A, 0x180E, 0x681F, 0xA01F, 0xD01F, 0xB016, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0570 (1392) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0580 (1408) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0590 (1424) pixels
0x0000, 0x0000, 0x0000, 0x59A0, 0xFEA0, 0xFFE0, 0xE7E0, 0xB7E0, 0x77E0, 0x3FE0, 0x17E0, 0x0761, 0x0423, 0x0040, 0x0000, 0x0000,   // 0x05A0 (1440) pixels
0x0000, 0x0000, 0x0000, 0x0042, 0x0066, 0x0007, 0x0002, 0x0001, 0x601D, 0xA01F, 0xD01F, 0xB016, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x05B0 (1456) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x05C0 (1472) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x05D0 (1488) pixels
0x0000, 0x0000, 0x0000, 0xBB80, 0xFEA0, 0xFFE0, 0xE7E0, 0xB7E0, 0x77E0, 0x3FA0, 0x0CC0, 0x0120, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x05E0 (1504) pixels
0x0000, 0x0000, 0x0000, 0x02D7, 0x01FF, 0x007F, 0x000A, 0x0000, 0x581A, 0xA01F, 0xD01F, 0xB016, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x05F0 (1520) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0600 (1536) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0610 (1552) pixels
0x0000, 0x0000, 0x0000, 0xCBC0, 0xFEA0, 0xFFE0, 0xE7E0, 0xA740, 0x44A0, 0x0900, 0x0000, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0620 (1568) pixels
0x0000, 0x0000, 0x0020, 0x033A, 0x01FF, 0x007F, 0x0004, 0x0000, 0x4815, 0xA01F, 0xD01F, 0xB016, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0630 (1584) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0640 (1600) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0650 (1616) pixels
0x0000, 0x0000, 0x0000, 0xD400, 0xFEA0, 0xFFE0, 0xA5C0, 0x10C0, 0x0060, 0x1B00, 0x0E00, 0x04C0, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0660 (1632) pixels
0x0000, 0x0000, 0x0041, 0x035C, 0x01FF, 0x007B, 0x0001, 0x0000, 0x3811, 0xA01F, 0xD01F, 0xB016, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0670 (1648) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0680 (1664) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0690 (1680) pixels
0x0000, 0x0000, 0x0820, 0xDC20, 0xFEA0, 0xFFE0, 0x52E0, 0x0000, 0x2260, 0x3FE0, 0x17E0, 0x0561, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x06A0 (1696) pixels
0x0000, 0x0000, 0x00A3, 0x039E, 0x01FF, 0x0057, 0x0000, 0x0000, 0x280C, 0xA01F, 0xD01F, 0xB016, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x06B0 (1712) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x06C0 (1728) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x06D0 (1744) pixels
0x0000, 0x0000, 0x1040, 0xE460, 0xFEA0, 0xF780, 0x1900, 0x0000, 0x08E0, 0x3F80, 0x17E0, 0x05E1, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x06E0 (1760) pixels
0x0000, 0x0000, 0x0105, 0x03BF, 0x01FF, 0x0052, 0x0000, 0x0000, 0x1807, 0xA01F, 0xD01F, 0xB016, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x06F0 (1776) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0700 (1792) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0710 (1808) pixels
0x0000, 0x0000, 0x2060, 0xF480, 0xFEA0, 0xC600, 0x0000, 0x0000, 0x0000, 0x3620, 0x17E0, 0x0621, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0720 (1824) pixels
0x0000, 0x0000, 0x0168, 0x03DF, 0x01FF, 0x002C, 0x0000, 0x0000, 0x0803, 0x981D, 0xD01F, 0xB016, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0730 (1840) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0740 (1856) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0750 (1872) pixels
0x0000, 0x0000, 0x2860, 0xFCC0, 0xFEA0, 0x8400, 0x0000, 0x0000, 0x0000, 0x2D20, 0x17E0, 0x0641, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0760 (1888) pixels
0x0000, 0x0000, 0x01EA, 0x03DF, 0x01FF, 0x0007, 0x0000, 0x0000, 0x0000, 0x881A, 0xD01F, 0xB016, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0770 (1904) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0780 (1920) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0790 (1936) pixels
0x0000, 0x0000, 0x38A0, 0xFCC0, 0xFEA0, 0x4A40, 0x0000, 0x0000, 0x0000, 0x1C00, 0x17E0, 0x06E1, 0x0040, 0x0000, 0x0000, 0x0000,   // 0x07A0 (1952) pixels
0x0000, 0x0000, 0x024D, 0x03DF, 0x01DE, 0x0003, 0x0000, 0x0000, 0x0000, 0x7016, 0xD01F, 0xB817, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x07B0 (1968) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x07C0 (1984) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x07D0 (2000) pixels
0x0000, 0x0000, 0x2880, 0xC3C0, 0xBCC0, 0x10A0, 0x0000, 0x0000, 0x0000, 0x09E0, 0x0E60, 0x0521, 0x0020, 0x0000, 0x0000, 0x0000,   // 0x07E0 (2016) pixels
0x0000, 0x0000, 0x01A9, 0x0319, 0x0133, 0x0000, 0x0000, 0x0000, 0x0000, 0x380B, 0xA819, 0x8811, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x07F0 (2032) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0800 (2048) pixels
};
