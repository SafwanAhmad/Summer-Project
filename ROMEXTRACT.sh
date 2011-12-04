
echo "Enter the name of the assembly file"
read NAME
gpasm $NAME.picasm

reset

ls 

echo "Passing .cod file to gpvc"

gpvc -r $NAME.cod > INPUT


gawk '/:/ { print $0}' INPUT | cut -f 2 -d ":" | tr -s " " "\n" | cut --bytes=2-4 > ROM


exit
