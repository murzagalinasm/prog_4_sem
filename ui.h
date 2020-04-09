class ui
{

private:

    /* data */
public:
    static ui();
    virtual int winx() = 0;
    virtual int winy() = 0;

    virtual void run(Game&) = 0;
    virtual void draw() = 0;
    virtual void quite() = 0;

    virtual ~ui();
};







