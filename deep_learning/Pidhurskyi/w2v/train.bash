for i in 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20; do
  input="model-500000texts-$((i - 1))epoch" 
  output="model-500000texts-${i}epoch" 
  echo "===================================================="
  echo " EPOCH #${i}"
  echo " INPUT  MODEL: ${input}"
  echo " OUTPUT MODEL: ${output}"
  echo "===================================================="
  ./test.py -l ${input} -t ${output} -n 500000 -j 4
done
