FROM python:3.7.10-buster
RUN mkdir /usr/src/app
WORKDIR /app2
COPY requirements.txt .

RUN pip install -r requirements.txt
CMD ["python", "-u", "/app2/main.py"]