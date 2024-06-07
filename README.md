# Haffman Archiver
## Описание
Архиватор, сделанный по алгоритму кодирования Хаффмана, сжимает текстовые файлы размером до 500 Кб. Архиватор вызывается из командной строки и записывает результат в изначально определённые файлы.
## Запуск\
-Для того, чтобы протестировать работу архиватора, необходимо запустить файл build.bat для Windows или файл build.sh для Linux, при этом соберётся исполнительный файл archiver с соответствующим расширением.
-Чтобы сжать текстовый файл в архив, необходимо в командной строке вызвать собранный ранее исполняемый файл в командной строке вместе с текстовым файлом и командой compress. Пример для Windows: "./archiver.exe input.txt compress". При этом закодированные данные запишутся в текстовый файл "en_input.txt".
-Чтобы распаковать сжатый файл, необходимо ввести команду unpack вместе с закодированным файлом. Пример для Windows: "./archiver.exe en_input.txt unpack". Распакованные данные запишутся в текстовый файл "output.txt".
