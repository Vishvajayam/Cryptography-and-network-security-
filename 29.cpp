#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define STATE_SIZE 25
#define CAPACITY_LANES 16
#define LANE_SIZE 64

typedef struct {
    uint64_t state[STATE_SIZE];
} InternalState;

void initializeState(InternalState *state) {
    for (int i = 0; i < STATE_SIZE; i++) {
        state->state[i] = 0;
    }
}

int allCapacityLanesNonzero(InternalState *state) {
    for (int i = 0; i < CAPACITY_LANES; i++) {
        if (state->state[i] == 0) {
            return 0;  
        }
    }
    return 1; 
}

int main() {
    InternalState state;
    initializeState(&state);
    
    srand(time(NULL));
    
    int steps = 0;
    while (!allCapacityLanesNonzero(&state)) {
        int laneToUpdate = rand() % CAPACITY_LANES;  
        int bitPosition = rand() % LANE_SIZE;        
        
        state.state[laneToUpdate] |= (1ULL << bitPosition);  
        
        steps++;
    }
    
    printf("All capacity lanes have at least one nonzero bit after %d steps.\n", steps);
    return 0;
}
