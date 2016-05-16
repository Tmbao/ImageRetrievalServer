g++ utils/compute_ap/compute_ap.cpp -o utils/compute_ap/compute_ap

for file in Dataset/rankedlists/*.txt; do
    filename=${file##*/}
    basename=${filename%_query.txt}
    echo $basename
    utils/compute_ap/compute_ap "Dataset/groundtruths/$basename" "Dataset/rankedlists/${basename}_query.txt" > "Dataset/ap/${basename}_query.txt"
done
