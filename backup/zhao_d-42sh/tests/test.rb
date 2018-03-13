#!/bin/ruby
require "open3"
require "find"
require "timeout"

class String
  def black; "\e[30m#{self}\e[0m" end
  def red; "\e[31m#{self}\e[0m" end
  def green; "\e[32m#{self}\e[0m" end
  def brown; "\e[33m#{self}\e[0m" end
  def blue; "\e[34m#{self}\e[0m" end
  def magenta; "\e[35m#{self}\e[0m" end
  def cyan; "\e[36m#{self}\e[0m" end
  def gray; "\e[37m#{self}\e[0m" end

  def bg_black; "\e[40m#{self}\e[0m" end
  def bg_red; "\e[41m#{self}\e[0m" end
  def bg_green; "\e[42m#{self}\e[0m" end
  def bg_brown; "\e[43m#{self}\e[0m" end
  def bg_blue; "\e[44m#{self}\e[0m" end
  def bg_magenta; "\e[45m#{self}\e[0m" end
  def bg_cyan; "\e[46m#{self}\e[0m" end
  def bg_gray; "\e[47m#{self}\e[0m" end

  def bold; "\e[1m#{self}\e[22m" end
  def italic; "\e[3m#{self}\e[23m" end
  def underline; "\e[4m#{self}\e[24m" end
  def blink; "\e[5m#{self}\e[25m" end
  def reverse_color; "\e[7m#{self}\e[27m" end
end

puts "\n      ╔╦╗╔═╗╔═╗╔╦╗  ╔═╗╦ ╦╦╔╦╗╔═╗"
puts "       ║ ║╣ ╚═╗ ║   ╚═╗║ ║║ ║ ║╣"
puts "       ╩ ╚═╝╚═╝ ╩   ╚═╝╚═╝╩ ╩ ╚═╝ \n\n"

failed = 0
success = 0
timeout = 0
total = 0
Dir.glob("../**/*.test") do |f|
  File.open(f, "r").each_line do |line|
    reference='bash --posix -c '
    testing='./42sh -c '
    reference << '"' + line + '"'
    testing << '"' + line + '"'
    a = {}
   # Timeout::timeout(1){
      Open3.popen3(reference) do |stdin , stdout , stderr , t|
        a [:stdout] = stdout.read
        a [:stderr] = stderr.read
        a [:status] = t.value.exitstatus
      end
 #   }
  #  Timeout::timeout(1){
      b = {}
      Open3.popen3(testing) do |stdin , stdout , stderr , t|
        b [:stdout] = stdout.read
        b [:stderr] = stderr.read
        b [:status] = t.value.exitstatus
      end
  #  }

    if a [:stdout] != b [:stdout] || a [:stderr] != b [:stderr]
      $stdout.puts "[FAILED] ".red + " #{line}"
      failed += 1
    else
      $stdout.puts "[SUCCESS]".green + " #{line}"
      success += 1
    end
  puts "\n"
  end
end
puts "[SUCCESS]".green + " #{success}  " + "[FAILED] ".red + " #{failed}  " \
  + "[TOTAL]".cyan + " #{success + failed}  " + "[TIMEOUT]".brown + " #{timeout} "

puts "\n"
