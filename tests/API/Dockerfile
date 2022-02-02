FROM python:3-slim

COPY . /api

RUN pip install -r requirements.txt

EXPOSE 5000

CMD ["python", "run.py"]
