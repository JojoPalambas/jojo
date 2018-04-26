# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.shortcuts import render
from django.http import HttpResponse

def main(request):
    return HttpResponse("""<h1> Welcome on the main page of page1!</h1>
                           <p>On apprécie.</p>""")
