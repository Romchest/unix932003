FROM ubuntu:23.10

RUN apt-get update && apt-get -y upgrade

WORKDIR /home

COPY script.sh /home/script.sh
RUN chmod +x /home/script.sh

CMD ["./script.sh"]
