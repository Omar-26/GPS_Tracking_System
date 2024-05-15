#include "../../utils/Std_Types.h"

extern void   SSI_INIT(void);
extern void   SSI_SEND_BYTE(uint8 BYTE);
extern uint8* SSI_RECEIVE_BYTE(void);
extern void   SSI_SEND_ARRAY_OF_BYTES(uint8* Pntr_To_array,uint32 size);
