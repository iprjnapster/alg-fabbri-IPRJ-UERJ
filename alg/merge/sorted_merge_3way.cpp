* R. Fabbri, 2024 */
#include "sorted_merge_3way.h"
#include <climits>

bool
sorted_merge_3way(
    const int *list_a, int na,
    const int *list_b, int nb,
    const int *list_c, int nc,
    int *list_abc)
{
    int i = 0;

    int a, b, c;

    for (a = 0; a < (na - 1); a++){
        if (list_a[a] > list_a[a + 1]){
            return false;
        }
    }
    
    for (b = 0; b < (nb - 1); b++){
        if (list_b[b] > list_b[b + 1]){
            return false;
        }
    }

    for (c = 0; c < (nc - 1); c++){
        if (list_c[c] > list_c[c + 1]){
            return false;
        }
    }

    a = 0;
    b = 0;
    c = 0;

    while (a < na || b < nb || c < nc){
        int a_value = (a < na) ? list_a[a] : INT_MAX;
        int b_value = (b < nb) ? list_b[b] : INT_MAX;
        int c_value = (c < nc) ? list_c[c] : INT_MAX;

        if (a_value <= b_value && a_value <= c_value){
            list_abc[i] = a_value;
            i++;
            a++;
        }
        else if (b_value <= a_value && b_value <= c_value){
            list_abc[i] = b_value; 
            i++;
            b++;
        }
        else{
            list_abc[i] = c_value;
            i++;
            c++;
        }
    }

    return true;
}
