#include "queue.h"
#include "tile_game.h"

//void enqueue(struct queue *q, struct game_state state) {}
void enqueue(struct queue *q, struct game_state state){
    size_t encoded = serialize(state);
    insert_at_tail(&q->data, encoded);

}

//struct game_state dequeue(struct queue *q) { return (struct game_state){0}; }
struct game_state dequeue(struct queue *q){
    size_t encoded = remove_from_head(&q->data);
    return deserialize(encoded);
}

//int number_of_moves(struct game_state start) { return 0; }
int number_of_moves(struct game_state start){
    /*
    if (is_solved(start)) return 0;

    struct queue q = {0};  //queue of states
    enqueue(&q, start);

    struct hash_table visited = {0};
    hash_table_init(&visited);

    while(q.data.head != NULL){
        struct game_state curr = dequeue(&q);
        size_t curr_encoded = serialize(curr);

        if (hash_table_contains(&visited, curr_encoded)){
            continue;
        }
        hash_table_insert(&visited,curr_encoded);
        struct game_state children[4];
        int num = generate_all_moves(curr,children);

        for (int i = 0; i < num; i++){
            struct game_state next = children[i];
            if(is_solved(next)){
                free_list(q.data);
                hash_table_destroy(&visited);
                return next.num_steps;
            }
            enqueue(&q,next);
        }
    }
    free_list(q.data);
    hash_table_destroy(&visited);
    */
    return -1;//unsolveble chance

}

