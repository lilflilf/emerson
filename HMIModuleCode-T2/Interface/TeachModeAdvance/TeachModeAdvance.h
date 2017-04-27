#ifndef TEACHMODEADVANCE_H
#define TEACHMODEADVANCE_H


class TeachModeAdvance
{
public:
    void _set();
    void _default();
public:
    static TeachModeAdvance* Instance();
private:
    TeachModeAdvance();
private:
    static TeachModeAdvance* _instance;
};

#endif // TEACHMODEADVANCE_H
