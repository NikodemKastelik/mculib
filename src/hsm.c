#include <hsm.h>

#define HSM_MAX_DEPTH 4

#define SWAP(x, y, type) {type tmp = x; x = y; y = tmp;} while(0)

static uint32_t hsm_state_depth_get(const hsm_state_t * state)
{
    uint32_t depth = 0;
    while (state)
    {
        depth++;
        state = state->parent;
    }
    return depth;
}

static const hsm_state_t * hsm_lca_get(const hsm_state_t * state1, const hsm_state_t * state2)
{
    uint32_t depth1 = hsm_state_depth_get(state1);
    uint32_t depth2 = hsm_state_depth_get(state2);

    if (depth1 > depth2)
    {
        SWAP(depth1, depth2, uint32_t);
        SWAP(state1, state2, const hsm_state_t *);
    }

    while (depth1 < depth2)
    {
        if (!state2)
        {
            return NULL;
        }
        state2 = state2->parent;
        depth2--;
    }

    while (state1 && state2)
    {
        if (state1 == state2)
        {
            return state1;
        }
        state1 = state1->parent;
        state2 = state2->parent;
    }

    return NULL;
}

static const hsm_state_t * hsm_lca_resolve(const hsm_state_t * current, const hsm_state_t * next)
{
    const hsm_state_t * state_lca;
    if (current == next)
    {
        // Self transition
        state_lca = current->parent;
    }
    else
    {
        state_lca = hsm_lca_get(current, next);
    }

    // Dispatch exit event till the LCA state is encountered
    while (current != state_lca)
    {
        (void)current->handler(HSM_EVENT_EXIT);
        current = current->parent;
    }

    // Build state tree from target to the LCA state
    const hsm_state_t * in_states[HSM_MAX_DEPTH];
    uint32_t idx = 0;
    while (next != state_lca)
    {
        in_states[idx++] = next;
        next = next->parent;
    }

    // Dispatch entry event on successive states in reverse order,
    // up to one state before the final one.
    while (idx > 1)
    {
       (void)in_states[--idx]->handler(HSM_EVENT_ENTRY);
    }
    return in_states[0];
}

void hsm_start(hsm_t * hsm, const hsm_state_t * initial_state)
{
    hsm->current = initial_state;
    hsm->next = NULL;
    hsm_dispatch(hsm, HSM_EVENT_ENTRY);
}

void hsm_dispatch(hsm_t * hsm, hsm_event_t evt)
{
    bool again;
    do
    {
        bool was_evt_handled;
        const hsm_state_t * state = hsm->current;
        do
        {
            was_evt_handled = state->handler(evt);
            state = state->parent;
        }
        while (!was_evt_handled && state);

        again = false;
        if (hsm->next)
        {
            hsm->current = hsm_lca_resolve(hsm->current, hsm->next);
            hsm->next = NULL;
            evt = HSM_EVENT_ENTRY;
            again = true;
        }
    }
    while (again);
}

void hsm_transition(hsm_t * hsm, const hsm_state_t * next)
{
    hsm->next = next;
}
