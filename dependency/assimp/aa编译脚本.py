import os
import shutil
import subprocess
import time

# 设置相关路径和命令
output_directory = "output"
destination_directory = "destination"
make_command = "mingw32-make"

# 清理输出目录
if os.path.exists(output_directory):
    shutil.rmtree(output_directory)
os.makedirs(output_directory)

# 执行mingw32-make命令
make_process = subprocess.Popen(make_command, shell=True, cwd=output_directory)
make_process.wait()

# 等待命令执行完毕
while make_process.poll() is None:
    time.sleep(1)

# 检查生成的文件
success = os.path.exists(os.path.join(output_directory, "generated_file.txt"))

if success:
    print("生成成功")
    # 拷贝生成的文件到指定目录
    generated_file_path = os.path.join(output_directory, "generated_file.txt")
    shutil.copy(generated_file_path, os.path.join(destination_directory, "copied_file.txt"))
else:
    print("生成失败，请查看日志")

# 如果生成失败，输出日志
if make_process.returncode != 0:
    print("生成过程中出现错误，返回码:", make_process.returncode)
