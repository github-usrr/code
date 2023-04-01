#!/usr/bin/env bash

repos_dir_name="repos-dir"

#if repos dir exists - clear it, if not - create repos dir
if [ -d "$repos_dir_name" ]; then
   cd $repos_dir_name
   rm -rf *
else
   mkdir $repos_dir_name
   cd $repos_dir_name
fi 


# Cloning
repos=(
    "https://github.com/openwrt/telephony.git"
    "https://github.com/openwrt/bcm63xx-cfe.git"
    "https://github.com/openwrt/packages-abandoned.git"
)


# Sequential cloning
start_time=$(date +%s)

for repo in ${repos[@]}
do
  git clone $repo
done

end_time=$(date +%s)
elapsed=$(( end_time - start_time ))
echo "----------------------------Sequential cloning: ${elapsed} secs-------------"


# Clear
rm -rf *


# Parallel cloning
start_time=$(date +%s)

for repo in ${repos[@]}
do
  git clone $repo &
done

#wait all jobs and then calc secs elapsed
wait
end_time=$(date +%s)
elapsed=$(( end_time - start_time ))
echo "----------------------------Parallel cloning: ${elapsed} secs-------------"
