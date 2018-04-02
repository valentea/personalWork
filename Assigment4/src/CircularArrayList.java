import java.util.ArrayList;

public class CircularArrayList<E> extends ArrayList<E>
{
    private static final long serialVersionUID = 1L;

    public E get(int index)
    {
        if (index == -1)
        {
            index = size()-1;
        }

        else if (index == size())
        {
            index = 0;
        }

        return super.get(index);
    }
}