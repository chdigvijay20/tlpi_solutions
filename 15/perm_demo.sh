op=$1

if [ $# == 0 ]; then
    printf "enter argument as one of create, read, write, delete, move\n"
    exit -1
fi

function do_op {
    case $op in
        create)
            touch dir/file.txt
            ;;

        read)
            cat dir/file.txt
            ;;

        write)
            echo "something" > dir/file.txt
            ;;

        delete)
            rm -f dir/file.txt
            ;;

        move)
            mv -f dir/file.txt dir/file_cp.txt
            ;;
    esac
}

if [ "$1" != "create" ]; then
    chmod 777 dir

    for i in {0..511}
    do
        fperm=`echo "obase=8; $i" | bc`
        chmod $fperm dir/file.txt

        do_op

        if [ $? -eq 0 ]; then
            printf "operation successful with file permission $fperm\n"
            if [ "$1" == "move" ]; then
                mv dir/file_cp.txt dir/file.txt
            fi

            if [ "$1" == "delete" ]; then
                touch dir/file.txt
                chmod $fperm dir/file.txt
            fi
            break
        fi
    done
fi

if [ "$1" == "create" ]; then
    chmod 777 dir
    rm -f dir/file.txt
fi

for i in {0..511}
do
    dperm=`echo "obase=8; $i" | bc`
    chmod $dperm dir

    do_op

    if [ $? -eq 0 ]; then
        printf "operation successful with dir permission $dperm\n"
        exit 0
    fi
done
