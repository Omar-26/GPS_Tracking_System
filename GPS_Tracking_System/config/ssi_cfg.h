/*Include of ssi_types.h*/
#include"../mcal/ssi/ssi_types.h"
/*ssi exeuction configuration ways*/
#define SSI_Execution_By_POLLING     0
#define SSI_Execution_By_Event_Based 1
#define SSI_Execution_By_Time_Based  2

/*Configure SSI execution way by choosing rom ssi exeuction configuration ways*/
#define SSI_Execution_Way SSI_Execution_By_POLLING            


/**Export or extern for ssi configuration structure**/
extern const str_SSI_Config_t str_SSI_Config; 
