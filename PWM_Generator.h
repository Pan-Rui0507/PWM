#ifndef _PWM_GENERATOR_H_
#define _PWM_GENERATOR_H_

extern void PWM_Init(unsigned int fre);
extern void PWM_generator();
extern void Dir_Change();
extern void duty1_set(unsigned char d1);
extern void duty2_set(unsigned char d2);
extern void duty_reset();
extern void duty1_alter(bit mode);
extern void duty2_alter(bit mode);

#endif 