struct animation {
    int clips;
    bool playing;
    int current = 0;
    bool cyclic;
    int time_step;
    char animation_clips[5];
};