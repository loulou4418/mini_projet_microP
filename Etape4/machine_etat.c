#include <stdint.h>;

void procedure_traitement_IT(void)
{
    typedef enum state_t
    {
        WAIT,
        RISE,
        CTE,
        FALL
    } state_t;

    static state_t state = WAIT;
    static uint16_t time = 0;
    static uint16_t DACValue = 0;

    switch (state)
    {
    case WAIT:
        time++;
        if (time >= 64)
        {
            state = RISE;
            time = 0;
        }
        break;

    case RISE:
        DACValue += 8;
        /* time : 1023/8 = 128 */
        if (DACValue >= 1023)
        {
            state = CTE;
            DACValue = 1023;
        }
        break;

    case CTE:
        time++;
        if (time >= 512)
        {
            state = FALL;
            time = 0;
        }
        break;

    case FALL:
        DACValue -= 8;
        /* time : 1023/8 = 128 */
        if (DACValue <= 0)
        {
            state = WAIT;
            DACValue = 0;
        }
        break;

    /* Etat defaut = erreur raz variables */
    default:
        state = WAIT;
        time = 0;
        DACValue = 0;
        break;
    }
}

/* si l'écriture de DACValue peut se faire dans la fonction
 * remplacer effectation par DAC_write 

 * sinon créer une variable globale et getter et setter
 */