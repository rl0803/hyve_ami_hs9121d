if [ $7 -eq 1 ]; then
  if [ "$5" = "-hsm" ]; then
	  openssl dgst -engine gem -$3 -sigopt rsa_padding_mode:pss -sign $4 -out $2 -binary $1
  fi

  if [ "$5" = "-nohsm" ]; then
	  openssl dgst -$3 -sigopt rsa_padding_mode:pss -sign $4 -out $2 -binary $1
  fi

  if [ "$5" = "-hsmkey" ]; then
	  openssl dgst -engine gem -$3 -sigopt rsa_padding_mode:pss -sign $4 -keyform engine -out $2 -binary $1
  fi

  openssl dgst -$3  -sigopt rsa_padding_mode:pss -verify $6 -signature $2 $1

else

  if [ "$5" = "-hsm" ]; then
	  openssl dgst -engine gem -$3 -sign $4 -out $2 -binary $1
  fi

  if [ "$5" = "-nohsm" ]; then
	  openssl dgst -$3 -sign $4 -out $2 -binary $1
  fi

  if [ "$5" = "-hsmkey" ]; then
	  openssl dgst -engine gem -$3 -sign $4 -keyform engine -out $2 -binary $1
  fi

  openssl dgst -$3 -verify $6 -signature $2 $1
fi

if [ $? -ne 0 ]; then
	rm -rf $2
fi 

