echo " ----------- Building using TX2 Config. -----------"
bazel build --config=jetson //jetson:all
echo " ----------- Clearing deployment directory on Jetson -----------"
sshpass -p "filename7" ssh alex@192.168.1.11 'rm -r /home/alex/PB-I2C && mkdir /home/alex/PB-I2C/'
echo "----------- Deploying Build Results -----------"
sshpass -p "filename7" scp -r bazel-bin/jetson/* alex@192.168.1.11:/home/alex/PB-I2C/
echo "----------- Built and Deployed! -----------"