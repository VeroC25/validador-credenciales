FROM jenkins/jenkins:lts-jdk21

USER root

RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      build-essential \
      make \
      file \
      git \
      cppcheck \
 && rm -rf /var/lib/apt/lists/*

ENV JAVA_OPTS="-Duser.timezone=America/Costa_Rica"

COPY plugins.txt /usr/share/jenkins/ref/plugins.txt
RUN jenkins-plugin-cli --plugin-file /usr/share/jenkins/ref/plugins.txt

USER jenkins
