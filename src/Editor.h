#ifndef __EDITOR_H__
#define __EDITOR_H__

struct levelData {

};

class Editor {
    public:
        bool editing;
        LevelData * levelData;
        Game currentGame;

        void newLevel ();
        void loadLevel (string filename);
        void saveLevel (string filename);

        void render ();
};

#endif