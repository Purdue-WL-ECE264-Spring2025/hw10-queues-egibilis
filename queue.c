#include "queue.h"
#include "tile_game.h"


int is_goal(struct game_state state){
    uint8_t goal[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}
    };

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if (state.tiles[i][j] != goal[i][j]){
                return 0;

            }
        }
    }
    return 1;
}

void enqueue(struct queue *q, struct game_state state){
    size_t encoded = serialize(state);
    insert_at_tail(&q->data, encoded);
}

struct game_state dequeue(struct queue *q){
    size_t encoded = remove_from_head(&q->data);
    return deserialize(encoded);
}

int number_of_moves(struct game_state start){
    if(is_goal(start)) return 0;

    struct queue q = {0};
    enqueue(&q,start);

    struct queue visited = {0};
    enqueue(&visited, start);

    while (q.data.head != NULL){
        struct game_state curr = dequeue(&q);

        struct game_state moves[4];
        moves[0] = curr; move_up(&moves[0]);
        moves[1] = curr; move_down(&moves[1]);
        moves[2] = curr; move_left(&moves[2]);
        moves[3] = curr; move_right(&moves[3]);

        for(int i = 0; i < 4; i++){

            if(moves[i].num_steps == curr.num_steps) continue;

            if(is_goal(moves[i])){
                free_list(q.data);
                free_list(visited.data);
                return moves[i].num_steps;
            }

            int already_visited = 0;
            struct list_node *node = visited.data.head;
            while(node != NULL){
                struct game_state visited_state = deserialize(node->value);

                int same = 1;
                for(int r = 0; r < 4 && same; r++){
                    for(int c = 0; c < 4 && same; c++){
                        if(moves[i].tiles[r][c] != visited_state.tiles[r][c]){
                            same = 0;
                        }
                    }
                }


                if(same){
                    already_visited = 1;
                    break;
                }
                node = node-> next;
            }

            if(!already_visited){
                enqueue(&q, moves[i]);
                enqueue(&visited,moves[i]);
            }
                
        }

    }
        free_list(q.data);
        free_list(visited.data);
        return -1;
}
                /*if(is_goal(moves[i], visited_state)){
                    already_visited = 1;
                    break;
                }
                node = node->next;
            }
            if(!already_visited){
                enqueue(&q,moves[i]);
                enqueue(&visited, moves[i]);
            }
        }
    }
    free_list(q.data);
    free_list(visited.data);
    return -1;
}


//IGNORE BELOW IM STUPID AF




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
    
    if (is_solved(start)) return 0;

    struct queue q = {0};  //queue of states
    enqueue(&q, start);

    struct queue visited = {0};

    while(q.data.head != NULL)
    {
        struct game_state curr = dequeue(&q);

        if(equals(curr)){
            free_list(q.data);
            free_list(visited.data);
            return curr.num_steps;
        }
        struct game_state next_state;

        next_state = curr;
        move_up(&next_state);

        if(next_state.num_steps > curr.num_steps && !been_to(next_state))
    }


    queue_init(&visited);

    while(q.data.head != NULL){
        struct game_state curr = dequeue(&q);
        size_t curr_encoded = serialize(curr);

        if (contains(&visited, curr_encoded)){
            continue;
        }
         game_state children[4];
        int num = generate_all_moves(curr,children);

        for (int i = 0; i < num; i++){
            struct game_state next = children[i];
            if(is_solved(next)){
                free_list(q.data);
                destroy(&visited);
                return next.num_steps;
            }
            enqueue(&q,next);
        }
    }
    free_list(q.data);
    destroy(&visited);
    
    return -1;//unsolveble chance

}
*/
