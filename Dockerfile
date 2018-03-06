# Use ODV runtime as a parent image
FROM kemekaze/odv_vdrift_base:latest


# Set the working directory to /app
WORKDIR /app

# Copy the app directory contents into the container at /app
ADD ./app /app

#Compile VDrift
RUN scons


CMD ["bash", "main.sh"]
