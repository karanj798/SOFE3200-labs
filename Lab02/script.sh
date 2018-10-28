#! /bin/sh
# Question 1
if [ "$#" = 0 ];then
    echo Question 1
    echo -----------
    cal -m $(eval date +%B)
    cal -y $(eval date +%Y)
fi

# Question 2
if [ "$#" = 1 ];then
    echo Question 2
    echo -----------
    cal -m $1
fi

# Question 3
if [ "$#" = 2 ];then
    echo Question 3
    echo -----------
    cal $1 $2
fi

# Question 4
if [ "$#" = 0 ];then
    echo Question 4
    echo -----------
    echo The current calendar year is: $(eval date +%Y)
fi

# Question 5
if [ "$#" = 2 ];then
echo Question 5
    echo -----------
    if [ `expr $2 % 4` = 0 ];then
        if [ `expr $2 % 100` = 0 ];then
            if [ `expr $2 % 400` = 0 ];then
                echo * $2 is a leap year.
            else
                echo * $2 is not a leap year.
            fi
        else
            echo * $2 is a leap year.
        fi
    else
        echo * $2 is not a leap year.
    fi
fi

# Question 6
echo Question 6
echo -----------
year=$(eval date +%Y)
while : ; do
    if [ `expr $year % 4` = 0 ];then
        if [ `expr $year % 100` = 0 ];then
            if [`expr $year % 400` = 0 ]; then
                echo $year is the next leap year.
                break
            else
                year=`expr $year + 1`
            fi
        else
            echo $year is the next leap year.
            break
        fi
    else
        year=`expr $year + 1`
    fi
done

