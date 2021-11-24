cd ./archive
f2c lowtran7.1.f 2>&1 ../logs/f2c-conversion.log
mv ./lowtran7.1.c ../sources/initial-lowtran7.1.c
cd ..