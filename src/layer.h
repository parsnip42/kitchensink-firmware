#ifndef INCLUDED_LAYER_H
#define INCLUDED_LAYER_H

class Layer
{
public:
    static const int Rows    = 5;
    static const int Columns = 20;
    
public:
    explicit Layer(const int (&mapping)[Rows][Columns]);

public:
    int at(int row, int column) const;
    
private:
    const int (&mMapping)[Rows][Columns];
};


inline
Layer::Layer(const int (&mapping)[Rows][Columns])
    : mMapping(mapping)
{ }

inline
int Layer::at(int row, int column) const
{
    if ((row >= 0) && (row < Rows)
        && (column >= 0) && (column < Columns))
    {
        return mMapping[row][column];
    }
    else
    {
        return 0;
    }
}

#endif
