from django.db import models
from django.contrib.postgres.fields import ArrayField


class RequestImage(models.Model):
    content = models.ImageField(upload_to='images/%Y/%m/%d')
    request_at = models.DateTimeField(auto_now_add=True)

    def __unicode__(self):
        return self.content.name


class ResponseRankedList(models.Model):
    request = models.OneToOneField(RequestImage, related_name='response', null=True, blank=True)
    STATUS_CHOICES = (
        ('P', 'Pending'),
        ('C', 'Completed'),
    )
    status = models.CharField(max_length=3, choices=STATUS_CHOICES, null=True, blank=True)
    content = ArrayField(models.CharField(max_length=200), blank=True, null=True)

    def get_status(self):
        for choice in self.STATUS_CHOICES:
            if self.status == choice[0]:
                return choice[1]
        return 'Unidentified Error'

    def __unicode__(self):
        return self.get_status()
